#include "FreeImage.h"
#include "glew.h"
#include "glut.h"
#include "shader.h"
#include <cmath>
#include <iostream>
#include <string>

#define PI 3.14159265358
using namespace std;

int windowSize[2] = { 600, 600 };
void display();
void idle();
void reshape(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);

GLuint program;
GLuint vboName;
GLuint vaoName; //created by us for the Vertex Array Object
GLuint texture;

// height and width of the texture image
int iWidth;
int iHeight;
//Initialize the shaders 
void shaderInit();


//test to check whether sphere is drawn
void mySphere(int slice, int stack);
//load the texture
void loadTexture(const char* pFilename);

//Number of vertices that will be sent to shader
long int verticeNumber;
double rotationDelta = (double)(1 / 365);
double rotationDistance ;


//Storing vertex datas that will be sent to shader
class VertexAttribute {
public:
	GLfloat position[3];
	void setPosition(float x, float y, float z) {
		position[0] = x;
		position[1] = y;
		position[2] = z;
	};
	GLfloat texture[2];
};

//debug function to check vertex array
void printArr(const VertexAttribute* vertices);
//Collecting vertex datas
VertexAttribute *drawTriangle();

VertexAttribute*  drawSphere(int slices, int stacks, int radius);

int main(int argc, char** argv) {	
	std::cout << "at beginning: " << (double)rotationDelta << " , " << rotationDistance << std::endl;
	glutInit(&argc, argv);
	glutInitWindowSize(windowSize[0], windowSize[1]);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("0616110, AndresPonce");

	glewInit();
	shaderInit();
	loadTexture("earth_texture_map.jpg");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

/*Instead of binding everything to the VBO, we can
create a VAO and just pass the pointer to the beginning 
of our vertices after we bind them right? */
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
	VertexAttribute *vertices;
	verticeNumber = 180 * 361 *2 ;
	vertices = drawSphere(180, 360, 1);


	//enabling the position part of the vertices to be passed to the shader input
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexAttribute)*verticeNumber, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(offsetof(VertexAttribute, position)));
	
	
	//linking the texture part of the arrray with the shader input	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,sizeof(VertexAttribute), (void*)(offsetof(VertexAttribute, texture)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0); //unbinding the previous VAO


}

void display() {   

	// viewing and modeling transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 3.0f,// eye
		0.0f, 0.0f, 0.0f,// center
		0.0f, 1.0f, 0.0f);// up

	// projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (GLfloat)512 / (GLfloat)512, 1, 500);

	// viewport transformation
	glViewport(0, 0, windowSize[0], windowSize[1]);

	glMatrixMode(GL_MODELVIEW);
	rotationDelta += (double)1 / 365;
	double newDistance = (double)rotationDelta + (double)1 / 365;
	glRotatef(newDistance, 0.0f, 1.0f, 0.0f);

	//Clear the buffer
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat pmtx[16];
	GLfloat mmtx[16];
	glGetFloatv(GL_PROJECTION_MATRIX, pmtx);
	glGetFloatv(GL_MODELVIEW_MATRIX, mmtx);
 	GLint pmatLoc = glGetUniformLocation(program, "Projection");
	GLint mmatLoc = glGetUniformLocation(program, "ModelView");


	//setting the shader sampler
	GLint texLoc = glGetUniformLocation(program, "ourTexture");
	
	//setting the program as part of the state
	glUseProgram(program);

	//input the modelview matrix into vertex shader
	glUniformMatrix4fv(pmatLoc, 1, GL_FALSE, pmtx);
	//input the rotation matrix into vertex shader
	glUniformMatrix4fv(mmatLoc, 1, GL_FALSE, mmtx);
	
	glScalef(10.0f, 10.0f, 10.0f);
	
	//activ-ing and binding the texture we're to use
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(texLoc, 0);
	

	glBindVertexArray(vaoName);


	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, verticeNumber);
	


	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glUseProgram(0);
	glPopMatrix();
	glutSwapBuffers();
}	

void loadTexture(const char* Filename)
{
	std::cout << "loading the texture" << std::endl;
	//enabling, loading and allocating memory for our image
	glEnable(GL_TEXTURE_2D);
	FIBITMAP* pImage = FreeImage_Load(FreeImage_GetFileType(Filename, 0), Filename);
	FIBITMAP* p32BitsImage = FreeImage_ConvertTo32Bits(pImage);
	int iWidth = FreeImage_GetWidth(p32BitsImage);
	int iHeight = FreeImage_GetHeight(p32BitsImage);

	//creating and binding the texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//setting the parameters for the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//actually generating the 2d image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, iWidth, iHeight, 0, 
		GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(p32BitsImage));

	//mipmaps are smaller versions of the image that use less resources when
	//entire image is not needed in original format
	glGenerateMipmap(GL_TEXTURE_2D);

	//deallocating the memory
	glBindTexture(GL_TEXTURE_2D, 0);
	FreeImage_Unload(p32BitsImage);
	FreeImage_Unload(pImage);

}
VertexAttribute *drawTriangle() {
	VertexAttribute *vertices;
	vertices = new VertexAttribute[verticeNumber];
	vertices[0].setPosition(0,0,0);
	vertices[1].setPosition(1,0,0);
	vertices[2].setPosition(0,1,0);
	return vertices;
}
void printArr(const VertexAttribute* vertices) {
	for (long int i = 0; i < verticeNumber; i++) {
		std::cout << "vertex " << i << " " << vertices[i].position[0] << " " << vertices[i].position[1] << " "
			<< vertices[i].position[2] << std::endl;
	}
}
/*I need to see if what I was doing wrong was not decalring the three
vertices of the tirangle together, I was going one */
VertexAttribute* drawSphere(int slices, int stacks, int radius)
{
	
	VertexAttribute* vertices = new VertexAttribute[slices * (stacks+1) * 2 ];
	double size = slices * (stacks + 1) * 2;
	double x, y, z;
	double delta = 0.5;
	double slice_step = 2 * PI / slices, stack_step = PI / stacks;
	long  int counter = 0;
	for (int i = 0; i < slices; i++) {
		for (int j = 0; j < stacks + 1; j++) {

			x = sin(j * stack_step) * cos(i * slice_step);
			y = cos(j * stack_step);
			z = sin(j * stack_step) * sin(i * slice_step);
			vertices[counter].setPosition(x, y, z);
		
			//vertices[counter].texture[0] =  (atan2(-(z), x) + PI)/2 * PI;
			//vertices[counter].texture[1]  = acos(-y) / PI;
			vertices[counter].texture[0] = 1 - (float)i  / slices;
			vertices[counter].texture[1] = 1 -  (float)j / stacks;
			counter++;


			x = sin((j)*stack_step) * cos((i + 1) * slice_step);
			y = cos((j)*stack_step);
			z = sin((j)*stack_step) * sin((i + 1) * slice_step);
			//vertices[counter].texture[0] = (atan2(-(z), x) + PI) / 2 * PI;
			//vertices[counter].texture[1] = acos(-y) / PI;
			vertices[counter].texture[0] = 1 - (float)(i + 1) /slices;
				vertices[counter].texture[1] =1  -(float)j / stacks;
			vertices[counter].setPosition(x, y, z);
			counter++;
		}
	}
	
	std::cout << "final counter: " << counter << std::endl;
	return vertices;
}
void mySphere(int slice, int stack)
{
	double x, y, z;
	double slice_step = 2 * PI / slice, stack_step = PI / stack;
	
	for (int i = 0; i < slice; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j < stack + 1; j++) {
			x = sin(j * stack_step) * cos(i * slice_step);
			y = cos(j * stack_step);
			z = sin(j * stack_step) * sin(i * slice_step);
			glNormal3d(x, y, z);
			glVertex3d(x, y, z);

			x = sin(j * stack_step) * cos((i + 1) * slice_step);
			y = cos(j * stack_step);
			z = sin(j * stack_step) * sin((i + 1) * slice_step);
			glNormal3d(x, y, z);
			glVertex3d(x, y, z);
		}
		glEnd();
	}
}
void reshape(GLsizei w, GLsizei h) {
	windowSize[0] = w;
	windowSize[1] = h;
}

void keyboard(unsigned char key, int x, int y) {

}

void idle() {
	glutPostRedisplay();
}