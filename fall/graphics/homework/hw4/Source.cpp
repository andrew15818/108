#include "FreeImage.h"
#include "glew.h"
#include "glut.h"
#include "shader.h"
#include <cmath>
#include <iostream>
#include <string>

#include<iostream>
#define PI 3.14159
using namespace std;
int windowSize[2] = { 600, 600 };
void display();
void idle();
void reshape(GLsizei w, GLsizei h);
void textureInit();
void keyboard(unsigned char key, int x, int y);
void initParticlesPosition();

void updateParticlesPosition();
GLint stacks = 20;
GLint slices = 20;
GLint radius = 2;
GLuint numParticles = 100000;
GLuint program;
GLuint vboName;
GLuint vboName2;
GLuint vboName3;
GLuint vaoName, vaoName2;
GLuint texture;
GLfloat scaleFactor = 1.0f;
long long int verticeNumber;
void shaderInit();

class VertexAttribute {
	public:
	GLfloat position[3];
	GLfloat normal[3];
	void setPosition(float x, float y, float z) 
	{
		position[0] = x;
		position[1] = y;
		position[2] = z;
	}
	void setNormal(float x, float y, float z)
	{
		normal[0] = x;
		normal[1] = y;
		normal[2] = z;
	}
};
class ParticleAttribute {
public:
	GLfloat position[3];
	GLfloat speed[3];
	GLfloat texture[2];                        
	GLfloat fade; //how much time we have left 
	GLfloat life; //how much we can take
	GLfloat colorRandom;
	void setPosition(float x, float y, float z)
	{
		position[0] = x;
		position[1] = y;
		position[2] = z;
	}
};

ParticleAttribute* particles;
ParticleAttribute* upParticles;
ParticleAttribute* downParticles;
VertexAttribute* vertices;
VertexAttribute* drawSphere(int slices, int stacks);
ParticleAttribute* initDirParticles(bool isUp);
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(windowSize[0], windowSize[1]);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("0616110, AndresPonce");

	glewInit();
	shaderInit();
	textureInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
void textureInit()
{
	//char  fileName = ;
	const char* fileNameP = "earth_texture_map.jpg";
	//1. Enable Texture

	glEnable(GL_TEXTURE_2D);
	//2. Load texture
	FIBITMAP* pImage = FreeImage_Load(FreeImage_GetFileType(fileNameP, 0), fileNameP);
	FIBITMAP* p32BitsImage = FreeImage_ConvertTo32Bits(pImage);
	int iWidth = FreeImage_GetWidth(p32BitsImage);
	int iHeight = FreeImage_GetHeight(p32BitsImage);
	//3. Generate texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//4. Set the texture warping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//5. Specify texture environment
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//6. Generate a two dimensional texture image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, iWidth, iHeight, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(p32BitsImage));
	//set filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	FreeImage_Unload(p32BitsImage);
	FreeImage_Unload(pImage);


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
	
	initParticlesPosition();
	//enabling the position part of the vertices to be passed to the shader input
	glEnableVertexAttribArray(0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particles) * numParticles, particles, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleAttribute), (void*)(offsetof(ParticleAttribute, position)));
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleAttribute), (void*)(offsetof(ParticleAttribute, life)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glGenVertexArrays(1, &vaoName2);
	glBindVertexArray(vaoName2);
	glGenBuffers(1, &vboName2);
	glBindBuffer(GL_ARRAY_BUFFER, vboName2);
	//handling the directional particles
	upParticles = initDirParticles(true);
	glBufferData(GL_ARRAY_BUFFER, sizeof(upParticles) * numParticles, upParticles, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);

	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); //unbinding the previous VAO	
}
void display() {
	//viewing and modeling transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt( 0.0f, 0.0f, 5.6f, //eye
		0.0f, 0.0f, 0.0f, //center
		0.0f, 1.0f, 0.0f //up
	);
	//projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (GLfloat)512 / (GLfloat)512, 1, 500);

	//viewport transformation
	glViewport(0, 0, windowSize[0], windowSize[1]);

	//Clear the buffer
	glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_MODELVIEW);

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
	//glUniformMatrix4fv(lightmmtx, 1, GL_FALSE, mmtxOriginal);

	updateParticlesPosition();


	glBindVertexArray(vaoName);
	glBindBuffer(GL_ARRAY_BUFFER, vboName);

	//initParticlesPosition();
	//enabling the position part of the vertices to be passed to the shader input
	glEnableVertexAttribArray(0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particles) * numParticles, particles, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleAttribute), (void*)(offsetof(ParticleAttribute, position)));
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleAttribute), (void*)(offsetof(ParticleAttribute, life)));
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleAttribute), (void*)(offsetof(ParticleAttribute, colorRandom)));
	
	glDrawArrays(GL_POINTS, 0, numParticles);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	/*
	//hopefully binding the second pair of textures?
	glBindBuffer(GL_ARRAY_BUFFER, vboName2);
	glEnableVertexAttribArray(1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(upParticles) * numParticles, upParticles, GL_STATIC_DRAW);
	glDrawArrays(GL_POINTS, 0, numParticles);
	*/
	glMatrixMode(GL_MODELVIEW);
	GLUquadric* quad = gluNewQuadric();
	scaleFactor -= .01f;
	if (scaleFactor < 0) { scaleFactor = 0; }
	
	gluSphere(quad, scaleFactor, slices, stacks);
	

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
	glutSwapBuffers();
}
void reshape(GLsizei w, GLsizei h) {
	windowSize[0] = w;
	windowSize[1] = h;
}
void keyboard(unsigned char key, int x, int y)
{

}
void idle() {
	glutPostRedisplay();
}
void printArr() {
	std::cout << particles[0].life << std::endl;
}
VertexAttribute* drawSphere(int slices, int stacks) {
	double x, y, z;
	double delta = 0.5;
	int radius = 1;
	long long  size = slices * (stacks + 1) * 2;
	double slice_step = 2 * PI / slices, stack_step = PI / stacks;
	long long int counter = 0;
	VertexAttribute* tmp = new VertexAttribute[slices* (stacks + 1) * 2];
	for (int i = 0; i < slices; i++) {
		for (int j = 0; j < stacks; j++) {
			x = sin(j * stack_step) * cos(i * slice_step) * radius;
			y = cos(j * stack_step) * radius;
			z = sin(j * stack_step) * sin(i * slice_step) * radius;
			//std::cout << "position " << counter << " should be: " << x << " " << y << " " << z << std::endl;
			tmp[counter].setPosition(x, y, z);
			tmp[counter].setNormal(x, y, z);

			counter++;

			x = sin(j * stack_step) * cos((i + 1) * slice_step) * radius;
			y = cos(j * stack_step) * radius;
			z = sin(j * stack_step) * sin((i + 1) * slice_step) * radius;
			tmp[counter].setPosition(x, y, z);
			tmp[counter].setNormal(x, y, z);
			counter++;
		}
	}

	return tmp;
}
void initParticlesPosition() 
{
	/*
	double x, y, z;
	double delta = 0.5;
	int radius = 1;
	// = slices * (stacks + 1) * 2;
	double slice_step = 2 * PI / slices, stack_step = PI / stacks;
	long long int counter = 0;
	particles = new ParticleAttribute[numParticles];
	for (int i = 0; i < slices; i++) {
		for (int j = 0; j < stacks;j++) {
			x = sin(j * stack_step) * cos(i * slice_step) * radius;
			y = cos(j * stack_step) * radius;
			z = sin(j * stack_step) * sin(i * slice_step) * radius;
			particles[counter].setPosition(x, y, z);
			counter++;

			x = sin(j * stack_step) * cos((i + 1) * slice_step) * radius;
			y = cos(j * stack_step) * radius;
			z = sin(j * stack_step) * sin((i + 1) * slice_step) * radius;
			particles[counter].setPosition(x, y, z);
			counter++;
		}
	}
	printArr();
	*/
	
	particles = new ParticleAttribute[numParticles];
	for (int i = 0; i < numParticles; i++) {
		 particles[i].position[0] = 0.0f;
		particles[i].position[1] = 0.0f;
		particles[i].position[2] = 0.0f;

		float stepi = 2 * PI / 180;
		int randomi = rand() % 180;
		float stepj = 2 * PI / 180;
		int randomj = rand() % 180;

		particles[i].speed[0] = sin(randomj * stepj) * cos(randomi * stepi)* 100.0f;
		particles[i].speed[1] = cos(randomj * stepj)* 100;
		particles[i].speed[2] = sin(randomj * stepj) * sin(randomi * stepi) * 500.0f;

		particles[i].life = 1.0f;
		particles[i].fade = GLfloat(rand() % 100) / 1000.0f + 0.003f; 
		particles[i].colorRandom = 0;
	}
	
}
ParticleAttribute* initDirParticles(bool isUp)
{
	int yMultiplier = (isUp) ? 1 : -1;
	ParticleAttribute* dirParticles = new ParticleAttribute[numParticles];
	float z = 0;
	for (int i = 0; i < numParticles; i++) {
		float x = static_cast<float> (rand()) / static_cast <float> (RAND_MAX);
		float y = static_cast<float> (rand()) / static_cast <float> (RAND_MAX);
		
		if (y < x) {
			y = x + 0.01;
		}
		dirParticles[i].setPosition(x, y, z);
		//std::cout << i << ":" << dirParticles[i].position[0] << "," << dirParticles[i].position[1] << std::endl;
	}
	return dirParticles;
}
void updateParticlesPosition() {
	long int elapsedTime= glutGet(GLUT_ELAPSED_TIME);
	//std::cout << "it's been " << elapsedTime << " ms" << std::endl;
	for (int i = 0; i < numParticles; i++) {
		particles[i].position[0] = particles[i].position[0] + particles[i].speed[0] / 10000.0;
		particles[i].position[1] = particles[i].position[1] + particles[i].speed[1] / 10000.0;
		particles[i].position[2] = particles[i].position[2] + particles[i].speed[2] / 10000.0;
		particles[i].colorRandom = ((rand() % 2) == 0) ? 1 : 0;
		particles[i].life -= particles[i].fade;

		//resetting particles
		if (particles[i].life < 0 && elapsedTime < 10,000) {
			//std::cout << " here " << std::endl;
			particles[i].life = 1.0f;
			particles[i].fade = float(rand() % 100) / 1000.0f + 0.003f;
			particles[i].position[0] = 0.0f;
			particles[i].position[1] = 0.0f;
			particles[i].position[2] = 0.0f;
		}
	}
	//printArr();
}