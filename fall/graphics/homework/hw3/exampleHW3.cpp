#include "FreeImage.h"
#include "glew.h"
#include "glut.h"
#include "shader.h"
#include <iostream>
#include <string>

#define PI 3.14159

using namespace std;

int windowSize[2] = { 600, 600 };
//float k[3] = {0.0f, 0.0f, 0.5f}; //values for the shading 
GLfloat lightPos[3] = { 1.1f, 1.0f, 1.3f };
float eyePos[3] = { 0.0f, 0.0f, 5.6f };
void display();
void idle();
void reshape(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);

GLuint program;
GLuint vboName;
GLuint vaoName;
long long int verticeNumber;
double global_radius;
//Initialize the shaders 
void shaderInit();
int stacks = 20;
int slices = 20;
int radius = 1;

bool isRotating = false;
double rotationDelta = (double) 1/365;
float ks = 0.5f;
float kd = 0.5f;
float ka = 0.5;
float k[3] = { ks, kd, ka };
//Storing vertex datas that will be sent to shader
class VertexAttribute {
public:
	GLfloat position[3];
	GLfloat normal[3];
	void setPosition(float x, float y, float z) {
		position[0] = x;
		position[1] = y;
		position[2] = z;
	};
	void setNormal(float x, float y, float z) {
		normal[0] = x;
		normal[1] = y;
		normal[2] = z;
	}
};

//Collecting vertex datas
VertexAttribute* vertices;
VertexAttribute* smallSphere;
VertexAttribute *drawTriangle();
VertexAttribute *drawSphere(int slice, int stack, double radius );
void lighting()
{ 
	GLint lightVec = glGetUniformLocation(program, "lightPos");
	glUniform4f(lightVec,  lightPos[0], lightPos[1], lightPos[2], 1);
}
void kValues() 
{	
	GLint kLocation = glGetUniformLocation(program, "k");
	glUniform3fv(kLocation, 1, k);
}
void viewerPos()
{
	GLint viewerPos = glGetUniformLocation(program, "eyePos");
	glUniform3fv(viewerPos, 3, eyePos);
}
int main(int argc, char** argv) {	
	glutInit(&argc, argv);
	glutInitWindowSize(windowSize[0], windowSize[1]);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("ComputerGraphicsDemo");

	glewInit();
	shaderInit();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

void shaderInit() {
	GLuint vert = createShader("Shaders/example.vert", "vertex");
	GLuint frag = createShader("Shaders/example.frag", "fragment");

	program = createProgram(vert, frag);

	//create and bind a new vertex array object
	//Test the sphere drawing with only the VBO
	glGenVertexArrays(1, &vaoName);
	glBindVertexArray(vaoName);


	//Generate a new buffer object
	glGenBuffers(1, &vboName);
	glBindBuffer(GL_ARRAY_BUFFER, vboName);

	//copy vertex data to the buffer object
	VertexAttribute* vertices;
	verticeNumber = 2 * slices * stacks;
	vertices = drawSphere(slices, stacks, radius);


	//enabling the position part of the vertices to be passed to the shader input
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexAttribute) * verticeNumber, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(offsetof(VertexAttribute, position)));


	//linking the texture part of the arrray with the shader input	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(offsetof(VertexAttribute, normal)));
	glEnableVertexAttribArray(1);

	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0); //unbinding the previous VAO



}

void display() {   
	// viewing and modeling transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 5.6f,// eye
		0.0f, 0.0f, 0.0f,// center
		0.0f, 1.0f, 0.0f);// up

	// projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (GLfloat)512 / (GLfloat)512, 1, 500);

	// viewport transformation
	glViewport(0, 0, windowSize[0], windowSize[1]);

	//Clear the buffer
	glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_MODELVIEW);
	if (isRotating) {
		rotationDelta += (double)1 / 365;
		glRotatef(rotationDelta, 0.0f, 1.0f, 0.0f);
	}
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat pmtx[16];
	GLfloat mmtx[16];
	GLfloat mmtxOriginal[16];
	glGetFloatv(GL_PROJECTION_MATRIX, pmtx);
	glGetFloatv(GL_MODELVIEW_MATRIX, mmtx);
 	GLint pmatLoc = glGetUniformLocation(program, "Projection");
	GLint mmatLoc = glGetUniformLocation(program, "ModelView");
	GLint lightmmtx = glGetUniformLocation(program, "LightView");

	glUseProgram(program);




	//input the modelview matrix into vertex shader
	glUniformMatrix4fv(pmatLoc, 1, GL_FALSE, pmtx);
	//input the rotation matrix into vertex shader
	glUniformMatrix4fv(mmatLoc, 1, GL_FALSE, mmtx);
	glUniformMatrix4fv(lightmmtx, 1, GL_FALSE, mmtxOriginal);
	
	//not rendering the sphere correctly :'(
	/*
	glScalef(0.05f, 0.05f, 0.05f);
	glTranslatef(1.1, 1.0, 1.3);
	glColor3f(0.24, 0.23, 0.23);
	GLUquadric* quad;
	quad = gluNewQuadric();
	gluSphere(quad, 01, slices, stacks);
	*/
	//glPopMatrix();
	

	//passing the lighting position to the vertex shader
	lighting();
	kValues();
	glBindVertexArray(vaoName);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, verticeNumber);
	glBindVertexArray(0);
	glutSwapBuffers();


}

VertexAttribute *drawTriangle() {
	VertexAttribute *vertices;
	vertices = new VertexAttribute[verticeNumber];
	vertices[0].setPosition(0,0,0);
	vertices[1].setPosition(1,0,0);
	vertices[2].setPosition(0,1,0);
	return vertices;
}

void reshape(GLsizei w, GLsizei h) {
	windowSize[0] = w;
	windowSize[1] = h;
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'o':
			std::cout << "supposed to be rotating" << std::endl;
			isRotating = !isRotating;
			rotationDelta = 0;
	}
}

void idle() {
	glutPostRedisplay();
}
VertexAttribute*  drawSphere(int slice, int stack, double  radius) {
	
	double x, y, z;
	double delta = 0.5;
	radius = 1;
	long long  size = slice * (stack + 1) * 2;
	double slice_step = 2 * PI / slice, stack_step = PI / stack;
	long long int counter = 0; 
	VertexAttribute* vertices = new VertexAttribute[slice * (stack + 1) * 2];
	for (int i = 0; i < slice; i++) {
		for (int j = 0; j < stack; j++) {
			x = sin(j * stack_step) * cos(i * slice_step) * radius ;
			y = cos(j * stack_step) * radius;
			z = sin(j * stack_step) * sin(i * slice_step)*radius;
			vertices[counter].setPosition(x, y, z);
			vertices[counter].setNormal(x, y, z);
			 
			counter++;

			x = sin(j * stack_step) * cos((i + 1) * slice_step) * radius ;
			y = cos(j * stack_step) * radius;
			z = sin(j * stack_step) * sin((i + 1) * slice_step)* radius;
			vertices[counter].setPosition(x, y, z);
			vertices[counter].setNormal(x, y, z);
			counter++;
		}
	}
	return vertices;
}