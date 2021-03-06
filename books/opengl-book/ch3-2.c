#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#define WINDOW_TITLE_PREFIX "Chapter 3"

typedef struct {
	float XYZW[4];
	float RGBA[4];
} Vertex;
int currentWidth = 600;
int currentHeight = 600;
int windowHandle = 0;
unsigned int frameCount = 0;
GLuint vertexShaderID;
GLuint fragmentShaderID;
GLuint programID;
GLuint vaoID;
GLuint vboID;
GLuint bufferID;
GLuint indexBufferID[2];
GLuint activeIndexBuffer = 0;

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
void keyboardFunction(unsigned char, int, int);
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
	glutKeyboardFunc(keyboardFunction);
}

void keyboardFunction(unsigned char key, int x, int y) {
	x = y;
	y = x;
	switch (key) {
		case 'T':
		case 't':
			activeIndexBuffer = (activeIndexBuffer == 1) ? 0 : 1;
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID[activeIndexBuffer]);
			break;
		default:
			break;
	}
}

void resizeFunction(int width, int height) {
	currentWidth = width;
	currentHeight = height;
	glViewport(0, 0, currentWidth, currentHeight);
}

void renderFunction(void) {
	frameCount++;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (activeIndexBuffer == 0) {
		glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_BYTE, NULL);
	}
	else {
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, NULL);
	}
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
	Vertex vertices[] = {
		/* center */
		{{ 0.0f,  0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
		/* top */
		{{-0.2f,  0.8f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
		{{ 0.2f,  0.8f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
		{{ 0.0f,  0.8f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
		{{ 0.0f,  1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
		/* bottom */
		{{-0.2f, -0.8f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
		{{ 0.2f, -0.8f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
		{{ 0.0f, -0.8f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
		{{ 0.0f, -1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
		/* left */
		{{-0.8f, -0.2f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
		{{-0.8f,  0.2f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
		{{-0.8f,  0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
		{{-1.0f,  0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
		/* right */
		{{ 0.8f, -0.2f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
		{{ 0.8f,  0.2f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
		{{ 0.8f,  0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
		{{ 1.0f,  0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}}
	};
	GLubyte indices[] = {
		/* top */
		 0,  1,  3,
		 0,  3,  2,
		 3,  1,  4,
		 3,  4,  2,
		/* bottom */
		 0,  5,  7,
		 0,  7,  6,
		 7,  5,  8,
		 7,  8,  6,
		/* left */
		 0,  9, 11,
		 0, 11, 10,
		11,  9, 12,
		11, 12, 10,
		/* right */
		 0, 13, 15,
		 0, 15, 14,
		15, 13, 16,
		15, 16, 14
	};
	GLubyte alternateIndices[] = {
		/* outer square border */
		 3,  4, 16,
		 3, 15, 16,
		15, 16,  8,
		15,  7,  8,
		 7,  8, 12,
		 7, 11, 12,
		11, 12,  4,
		11,  3,  4,
		/* inner square */
		 0, 11,  3,
		 0,  3, 15,
		 0, 15,  7,
		 0,  7, 11
	};
	GLenum errorCheckValue = glGetError();
	const size_t bufferSize = sizeof(vertices);
	const size_t vertexSize = sizeof(vertices[0]);
	const size_t rgbOffset = sizeof(vertices[0].XYZW);
	glGenBuffers(1, &vboID);
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, vertexSize, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertexSize, (GLvoid *)rgbOffset);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glGenBuffers(2, indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof alternateIndices, alternateIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID[0]);
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
	glDeleteBuffers(1, &vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(2, indexBufferID);
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
