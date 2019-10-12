
//Your Student ID is XXXXXXX. (Modify it)
#include "glut.h"
#include <iostream>
#include "math.h"
using namespace std;

void drawSun();
void drawEarth();
void drawMars();
void display();
void reshape(int _width, int _height);
void keyboard(unsigned char key, int x, int y);
void idle();

int width = 400, height = 400;
int X = 1; //default degree value, you can adjust it
//we declare these as global becuase we will change them later
int earthSlices = 360;
int earthStacks = 180; 
GLfloat Y = 0.5; //default radius value, you can adjust it

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

void display()
{   	
	// TO DO: Set the MVP transform
	// Modeling/Viewing Transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	//Maybe they weren't showing up becuase the look at was incorrect?
	gluLookAt(0.0f, 30.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);	
	//gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//Proejction Transformation	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
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
	//glColor3s(1.0f, 0.0f, 0.0f);
	drawSun();	
	glPushMatrix();

	/*Handling the earth*/
	glRotatef(0.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(10.0f, 10.0f ,0.0f);
	drawEarth();

	//creating the axis on the earth
	//GLUquadric *quadric= gluNewQuadric();
	//gluCylinder(quadric,10.0f, 10.0f, 0.0f,10, 10);
	//glPopMatrix();	

	//popping the earth matrix to create and transform mars
	glPopMatrix();	

	//pushing the sun's array, isn't this already in the stack?  
	glPushMatrix();

	/*Handling Mars*/
	glRotatef(0.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(5.0f, 15.0f, 0.0f);
	//glColor3f(1.0f, 0.0f, 0.0f);
	/*alterantively, we could just write a drawPlanet() function? Instead of having the same function three times*/
	drawMars();
	glPopMatrix();
	glutSwapBuffers();
}
void drawSun(){
	const double radius = 7 * Y;
	int stacks = 60, slices = 240;

	for(int i=0; i<=stacks;i++){
		//need to create the triangles that we will be using
		double p1Latitude = M_PI * (-0.5 + (double)(i-1)/stacks);
		double p1sinx = sin(p1Latitude);
		double p1cosx = cos(p1Latitude);

		double p2Latitude = M_PI * (-0.5 + (double)i/stacks);
		double p2sinx = sin(p2Latitude);
		double p2cosx = cos(p2Latitude);
		glBegin(GL_QUAD_STRIP);
	
		for(int j=0; j<=slices; j++){	
			double longitude = 2 * M_PI * (-0.5+(double )(j-1)/slices);
			double longSinx = sin(longitude);
			double longCosx = cos(longitude);
			//first point of the quadrilateral
			glColor3f(1.0f, 0.0f, 0.0f );			
			glVertex3f(radius * longSinx  * p1cosx, radius *longCosx * p1cosx , radius * p1sinx);	
			glNormal3f(radius * longSinx  * p1cosx, radius *longCosx * p1cosx , radius * p1sinx);	
		
			//second point of the quadrialteral
			//glColor3f(1.0f, 0.0f, 0.0f );		
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
	if(key == 'O'){
		int temp  = earthSlices;
		earthSlices = earthStacks;
		earthStacks = temp;
	}
	
	
}

void idle() {	
	glutPostRedisplay();
}
