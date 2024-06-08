#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>


void RenderSceneCB() {
	static GLfloat mods[4] = {1.0f, -.9f, 0.8f, -0.7f};
	static GLfloat colors[4] = {50.0f/256.0f, 0.0f/256.0f, 200.0f/256.0f, 50.0f/256.0f};
	glClearColor(colors[0], colors[1], colors[2], 1.0f);

	for (int i = 0; i < 4; i++) {
		colors[i] += mods[i] * (1.0f / 2560.0);
		if (colors[i] >= 1.0f || colors[i] <= 0.0f) {
			mods[i] *= -1.0f;
		}
	}

	glClear(GL_COLOR_BUFFER_BIT);
	glutPostRedisplay();
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glewExperimental = GL_TRUE;
	glewInit();
	
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