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
	glDrawArrays(GL_POINTS, 0, 1);

	glDisableVertexAttribArray(0);

	glutSwapBuffers(); 

}

static void CreateVertexBuffer() {
	Vec3f vertices[1];
	vertices[0] = { };

	// Number of handles, pointer to GLuint array for x handles
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	int size[2] = { 1920, 1080 };
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