#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#define WINDOW_TITLE_PREFIX "Chapter 1"

int currentWidth = 800;
int currentHeight = 600;
int windowHandle = 0;

void initialize(int, char *[]);
void initWindow(int, char *[]);
void resizeFunction(int, int);
void renderFunction(void);

int main(int argc, char *argv[]) {
	initialize(argc, argv);

	glutMainLoop();

	exit(EXIT_SUCCESS);
}

void initialize(int argc, char *argv[]) {
	initWindow(argc, argv);	

	fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void initWindow(int argc, char *argv[]) {
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
			GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(currentWidth, currentHeight);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	windowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

	if (windowHandle < 1) {
		fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
		exit(EXIT_FAILURE);
	}

	glutReshapeFunc(resizeFunction);
	glutDisplayFunc(renderFunction);
}

void resizeFunction(int width, int height) {
	currentWidth = width;
	currentHeight = height;
	glViewport(0, 0, currentWidth, currentHeight);
}

void renderFunction(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();

	glutPostRedisplay();
}
