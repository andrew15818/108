
//Your Student ID is XXXXXXX. (Modify it)
#include "glut.h"
#include <iostream>
#include "math.h"
using namespace std;

void drawSun();
void drawEarth();
void drawMars();
void handlePlanet(GLfloat*, GLfloat*); //rotate and tranlsate the planet
void display();
void reshape(int _width, int _height);
void keyboard(unsigned char key, int x, int y);
void idle();

int width = 400, height = 400;
int X = 1; //default degree value, you can adjust it

//we declare these as global becuase we will change them later
int earthSlices = 360;
int earthStacks = 180; 

//color vertices for the different bodies
float earthColors[] = {0.0f, 0.0f, 1.0f, 0.0f};
float sunColors[] = {1.0f, 0.0f, 0.0f, 0.0f};
float cylinderColors[] = {0.0f, 1.0f, 0.0f, 0.0f};

GLfloat eAngle = 0, mAngle = 0; //test values i'll be using for the rotations
GLfloat Y = 0.5, radianConvert = 180/M_PI; //default radius value, you can adjust it

bool simulating = true;

void lighting()
{
	// enable lighting
	glEnable(GL_LIGHTING);
	//Add directed light
	GLfloat diffuseColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat ambientColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glEnable(GL_LIGHT0);								//open light0
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);	    //set diffuse color of light0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);	    //set ambient color of light0
	glLightfv(GL_LIGHT0, GL_POSITION, position);		//set position of light0
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("HW1");

	lighting();
	glutDisplayFunc(display);
	
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
GLUquadric *quad = gluNewQuadric();
void display()
{   	
	// TO DO: Set the MVP transform
	// Modeling/Viewing Transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	

	//gluLookAt(0.0f, 30.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);	//actual view we're supposed to use
	gluLookAt(0.0f, 0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);	//horizontal view for debugging only

	//Proejction Transformation	
	
	glMatrixMode(GL_PROJECTION); glLoadIdentity();	
	gluPerspective(45, width / (GLfloat)height, 0.1, 1000);

	//viewport
	glViewport(0,0, width, height);

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);		//remove back face
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);		//normalized normal 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// TO DO: Draw the Sun, Earth, Moon

	//you have to draw the shapes large enough so that they show :/
	//maybe try to use the vertex buffers so we dont render the spheres always ? 
	glMatrixMode(GL_MODELVIEW);

			drawSun();	
			//glPushMatrix();

			/*Handling the earth*/
			glTranslatef(18*Y*cos((eAngle*M_PI)/180),  0.0f,18*Y*sin((M_PI*eAngle)/180));
			glRotatef(eAngle+=(X*0.365), 0.0f,1.0f ,0.0f);		
			glPushMatrix();	//push the matrix now so we dont save the axis tilt for later
			glRotatef(23.5f, 1.0f, 0.0f, 0.0f);
			drawEarth();	

			/*Handling the axis cylinder, set the color directly here*/
			glMaterialfv(GL_FRONT, GL_DIFFUSE, cylinderColors);
			glTranslatef(0,3*Y,0);
			glRotatef(90, 1.0f, 0.0f, 0.0f);	
			gluCylinder(quad, .2,.2,5*Y,4,10);
				

			/*handling the moon/mars */	
			glPopMatrix();	//removing the changes we made for the axis, use earth's position	
			glTranslatef(3*Y*cos((mAngle*M_PI)/180),  0.0f,3*Y*sin((mAngle*M_PI)/180)); //cos, sin, use radians, not degrees
			glRotatef(mAngle+=(X*0.280),20*Y*cos(eAngle), 0.0f, 20*Y*sin(eAngle));	
			drawMars();
	
	glutSwapBuffers();
}
void handlePlanet(GLfloat* eAngle, GLfloat* rquad)
{
	*eAngle += 0.2f;
	glTranslatef(10,10,0);
	glRotatef(*eAngle, 0.0f, 0.0f, 0.0f);
	
	return;
}
void drawSun(){
	const double radius = 7 * Y;
	int stacks = 60, slices = 240;
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(int i=0; i<=stacks;i++){
		//need to create the triangles that we will be using
		double p1Latitude = M_PI * (-0.5 + (double)(i-1)/stacks);
		double p1sinx = sin(p1Latitude);
		double p1cosx = cos(p1Latitude);

		double p2Latitude = M_PI * (-0.5 + (double)i/stacks);
		double p2sinx = sin(p2Latitude);
		double p2cosx = cos(p2Latitude);

		glMaterialfv(GL_FRONT, GL_DIFFUSE,  sunColors);	
		glBegin(GL_QUAD_STRIP);	
		for(int j=0; j<=slices; j++){	
			double longitude = 2 * M_PI * (-0.5+(double )(j-1)/slices);
			double longSinx = sin(longitude);
			double longCosx = cos(longitude);
			//first point of the quadrilateral


			glVertex3f(radius * longSinx  * p1cosx, radius *longCosx * p1cosx , radius * p1sinx);		
			glNormal3f(radius * longSinx  * p1cosx, radius *longCosx * p1cosx , radius * p1sinx);	
		
			//second point of the quadrialteral

			glVertex3f(radius * longSinx  * p2cosx, radius *longCosx * p2cosx , radius * p2sinx);	
			glNormal3f(radius * longSinx  * p2cosx, radius *longCosx * p2cosx , radius * p2sinx);		
		}
		glEnd();
	}
}
void drawEarth(){
	//creating the earth	
	double radius = 2 * Y;
	for(int i =0; i<=earthStacks; i++){
		double p1Latitude = M_PI * (-0.5 + (double)(i-1)/earthStacks);
		double p1sinx = sin(p1Latitude);
		double p1cosx = cos(p1Latitude);

		double p2Latitude = M_PI * (-0.5 + (double) i/earthStacks);
		double p2sinx = sin(p2Latitude);
		double p2cosx = cos(p2Latitude);
		glBegin(GL_QUAD_STRIP);

		glMaterialfv(GL_FRONT, GL_DIFFUSE, earthColors);
		for(int j = 0; j <= earthSlices; j++){
			double longitude =  2* M_PI * (-0.5 + (double)(j-1)/earthSlices);
			double longSinx = sin(longitude);
			double longCosx = cos(longitude);

			glVertex3f(radius * longSinx * p1cosx, radius * longCosx * p1cosx, radius * p1sinx);
			glNormal3f(radius * longSinx * p1cosx, radius * longCosx * p1cosx, radius * p1sinx);

			glVertex3f(radius * longSinx * p2cosx, radius * longCosx * p2cosx, radius * p2sinx);
			glNormal3f(radius * longSinx * p2cosx, radius * longCosx * p2cosx, radius * p2sinx);
		}
		glEnd();
	}
	//drawing the cylinder accross the pole	
}
void drawMars(){
	int slices = 240;
	int stacks = 60;
	double radius = Y;
	for(int i = 0; i <= stacks; i++ ){
		double p1Latitude = M_PI * (-0.5 + (double)(i-1)/stacks);
		double p1sinx = sin(p1Latitude);
		double p1cosx = cos(p1Latitude);

		double p2Latitude = M_PI * (-0.5 + (double)i/stacks);
		double p2sinx = sin(p2Latitude);
		double p2cosx = cos(p2Latitude);
		
		glBegin(GL_QUAD_STRIP);
		for(int j = 0; j <= slices; j++){
			double longitude = 2 * M_PI * (-0.5 + (double)(j-1)/slices);
			double longSinx = sin(longitude);
			double longCosx = cos(longitude);

			glVertex3f(radius * longSinx * p1cosx, radius * longCosx * p1cosx, radius * p1sinx);
			glNormal3f(radius * longSinx * p1cosx, radius * longCosx * p1cosx, radius * p1sinx);
			
			glVertex3f(radius * longSinx * p2cosx, radius * longCosx * p2cosx, radius * p2sinx);
			glNormal3f(radius * longSinx * p2cosx, radius * longCosx * p2cosx, radius * p2sinx);
		}
		glEnd();
	}
}
void reshape(int _width, int _height) {
	width = _width;
	height = _height;
}


void keyboard(unsigned char key, int x, int y) {
	// TO DO: Set the keyboard control
	switch(key){
			case 'o':
				earthStacks = x;
				earthSlices = y;
				break;
			case 'p':
				simulating = !simulating;
	}
	/*
	if(key == 'O'){
		int temp  = earthSlices;
		earthSlices = earthStacks;
		earthStacks = temp;
	}
	if(key =='p'){
		simulating = !simulating;	
	}	
*/	
}

void idle() {	
	glutPostRedisplay();
}
