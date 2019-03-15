#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#define WINDOW_TITLE_PREFIX "Chapter 1"

int currentWidth = 800;
int currentHeight = 600;
int windowHandle = 0;
unsigned int frameCount = 0;

void initialize(int, char *[]);
void initWindow(int, char *[]);
void resizeFunction(int, int);
void renderFunction(void);
void timerFunction(int);
void idleFunction(void);

int main(int argc, char *argv[]) {
	initialize(argc, argv);

	glutMainLoop();

	exit(EXIT_SUCCESS);
}

void initialize(int argc, char *argv[]) {
	GLenum glewInitResult;

	initWindow(argc, argv);	

	glewInitResult = glewInit();

	if (GLEW_OK != glewInitResult) {
		fprintf(stderr, "ERROR: %s\n", glewGetErrorString(glewInitResult));
		exit(EXIT_FAILURE);
	}

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

	glutIdleFunc(idleFunction);
	glutTimerFunc(0, timerFunction, 0);
}

void resizeFunction(int width, int height) {
	currentWidth = width;
	currentHeight = height;
	glViewport(0, 0, currentWidth, currentHeight);
}

void renderFunction(void) {
	frameCount++;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();

	glutPostRedisplay();
}

void idleFunction(void) {
	glutPostRedisplay();
}

void timerFunction(int value) {
	if (value != 0) {
		char *tempString = malloc(512 + strlen(WINDOW_TITLE_PREFIX));

		sprintf(tempString, "%s: %d frames per second @ %d x %d",
				WINDOW_TITLE_PREFIX, frameCount * 4, currentWidth,
				currentHeight);

		glutSetWindowTitle(tempString);
		free(tempString);
	}

	frameCount = 0;
	glutTimerFunc(250, timerFunction, 1);
}
