#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#define WINDOW_TITLE_PREFIX "Chapter 2"

int currentWidth = 800;
int currentHeight = 600;
int windowHandle = 0;
unsigned int frameCount = 0;
GLuint vertexShaderID;
GLuint fragmentShaderID;
GLuint programID;
GLuint vaoID;
GLuint vboID;
GLuint colorBufferID;

const GLchar *vertexShader = \
	"#version 400\n"\

	"layout(location=0) in vec4 in_Position;\n"\
	"layout(location=1) in vec4 in_Color;\n"\
	"out vec4 ex_Color;\n"\

	"void main(void) {\n"\
	"	gl_Position = in_Position;\n"\
	"	ex_Color = in_Color;\n"\
	"}\n";

const GLchar *fragmentShader = \
	"#version 400\n"\

	"in vec4 ex_Color;\n"\
	"out vec4 out_Color;\n"\

	"void main(void) {\n"\
	"	out_Color = ex_Color;\n"\
	"}\n";

void initialize(int, char *[]);
void initWindow(int, char *[]);
void resizeFunction(int, int);
void renderFunction(void);
void timerFunction(int);
void idleFunction(void);
void cleanup(void);
void createVBO(void);
void destroyVBO(void);
void createShaders(void);
void destroyShaders(void);

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

	createShaders();
	createVBO();

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

	/* callback functions */
	glutReshapeFunc(resizeFunction);
	glutDisplayFunc(renderFunction);
	glutIdleFunc(idleFunction);
	glutTimerFunc(0, timerFunction, 0);
	glutCloseFunc(cleanup);
}

void resizeFunction(int width, int height) {
	currentWidth = width;
	currentHeight = height;
	glViewport(0, 0, currentWidth, currentHeight);
}

void renderFunction(void) {
	frameCount++;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

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

void cleanup(void) {
	destroyShaders();
	destroyVBO();
}

void createVBO(void) {
	GLfloat vertices[] = {
		-0.8f,  0.8f, 0.0f, 1.0f,
		 0.8f,  0.8f, 0.0f, 1.0f,
		-0.8f, -0.8f, 0.0f, 1.0f,
		 0.8f, -0.8f, 0.0f, 1.0f
	};

	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};

	GLenum errorCheckValue = glGetError();

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &colorBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	errorCheckValue = glGetError();
	if (errorCheckValue != GL_NO_ERROR) {
		fprintf(stderr, "ERROR: Could not create a VBO: %s\n",
				gluErrorString(errorCheckValue));

		exit(EXIT_FAILURE);
	}
}

void destroyVBO(void) {
	GLenum errorCheckValue = glGetError();

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &colorBufferID);
	glDeleteBuffers(1, &vboID);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vaoID);

	errorCheckValue = glGetError();
	if (errorCheckValue != GL_NO_ERROR) {
		fprintf(stderr, "ERROR: Could not destroy the VBO: %s\n",
				gluErrorString(errorCheckValue));

		exit(EXIT_FAILURE);
	}
}

void createShaders(void) {
	GLenum errorCheckValue = glGetError();

	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexShader, NULL);
	glCompileShader(vertexShaderID);

	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentShader, NULL);
	glCompileShader(fragmentShaderID);

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	glUseProgram(programID);

	errorCheckValue = glGetError();
	if (errorCheckValue != GL_NO_ERROR) {
		fprintf(stderr, "ERROR: Could not create the shaders: %s\n",
				gluErrorString(errorCheckValue));

		exit(EXIT_FAILURE);
	}
}

void destroyShaders(void) {
	GLenum errorCheckValue = glGetError();

	glUseProgram(0);

	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);

	glDeleteShader(fragmentShaderID);
	glDeleteShader(vertexShaderID);

	glDeleteProgram(programID);

	errorCheckValue = glGetError();
	if (errorCheckValue != GL_NO_ERROR) {
		fprintf(stderr, "ERROR: Could not destroy the shaders: %s\n",
				gluErrorString(errorCheckValue));

		exit(EXIT_FAILURE);
	}
}
