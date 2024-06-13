#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math_vector.hpp>

static void RenderSceneCB();
static void CreateVertexBuffer();
int main(int, char**);

GLuint VBO;

static void RenderSceneCB() {
	// Clear the window
	glClear(GL_COLOR_BUFFER_BIT);

	// Bind the gl array buffer to the global VBO object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Enable changing of position (attribute 0)
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// How to interpret arrays, where to start, how many to process
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glutSwapBuffers(); 

}

static void CreateVertexBuffer() {
	/*
	  Culling means that any triangle assembled
	  in a clockwise order will not be rendered
	  as it is facing the 'back' side, meaning
	  it is no longer visible
	*/
	glEnable(GL_CULL_FACE);
	
	/*
	  Changes which vertex order (CW, CCW) is
	  considered 'front facing'
	*/
	glFrontFace(GL_CW);

	/*
	  Tells OGL which face to cull, front or back
	*/
	glCullFace(GL_FRONT);
	

	Vec3f vertices[6] = {
		{-1.0f, -1.0f, 0.0f}, //left
		{ .25f, -1.0f, 0.0f}, //right
		{-.25f,  1.0f, 0.0f}, //top
		{-.25f,  1.0f, 0.0f}, //left
		{ .25f, -1.0f, 0.0f}, //bottom
		{ 1.0f,  1.0f, 0.0f}  //right
};
	
	// Number of handles, pointer to GLuint array for x handles
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	int size[2] = { 720, 480 };
	glutInitWindowSize(size[0], size[1]);

	int pos[2] = { 0, 0 };
	glutInitWindowPosition(pos[0], pos[1]);

	int window = glutCreateWindow("Point Example");
	std::cout << "Window ID: " << window << std::endl;

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error '%s'\n", glewGetErrorString(res));
		return 1;
	}

	CreateVertexBuffer();

	/*
	 Attaches RenderSceneCB (callback) as the function to call when the
	 display is set to be updated. This function must handle all the
	 necessary steps to actually render said display
	*/
	glutDisplayFunc(RenderSceneCB);

	/* 
	 Needs to be the last function call of main 
	 as glutMainLoop never returns
	*/
	glutMainLoop();

	return 0;
}