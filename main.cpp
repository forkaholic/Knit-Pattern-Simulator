#include <GL/freeglut.h>
#include <iostream>

void RenderSceneCB() {
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(1024, 720);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Temporary Name");
	glutDisplayFunc(RenderSceneCB);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glutMainLoop();
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();

	return 0;
}