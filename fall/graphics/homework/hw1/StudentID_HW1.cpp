
//Your Student ID is 0616110. (Modify it)
#include "glut.h"
#include <iostream>
#include "math.h"
using namespace std;

void drawSun();
void display();
void reshape(int _width, int _height);
void keyboard(unsigned char key, int x, int y);
void idle();

int width = 400, height = 400;
int X = 1; //default degree value, you can adjust it
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
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();	
	gluLookAt(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, width/ (GLfloat)height, 0.1, 1000);	

	//setting up the viewport matrix
	glViewport(0,0,width, height);	


	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);		//remove back face
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);		//normalized normal 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LEQUAL);
    
	// TO DO: Draw the Sun, Earth, Moon



	//drawSun();	
	//glPushMatrix();	
	
	glutSwapBuffers();

}
void drawSun(){

	glBegin(GL_TRIANGLE_STRIP);
	glutSolidSphere(69,69,69);
	glEnd();


}
void reshape(int _width, int _height) {
	width = _width;
	height = _height;
}


void keyboard(unsigned char key, int x, int y) {
	// TO DO: Set the keyboard control
	
	
	
}

void idle() {	
	glutPostRedisplay();
}
