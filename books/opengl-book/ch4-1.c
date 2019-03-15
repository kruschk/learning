#include "utils.h"
#define WINDOW_TITLE_PREFIX "Chapter 4"

int currentWidth = 800;
int currentHeight = 600;
int windowHandle = 0;
unsigned int frameCount = 0;
float cubeRotation = 0;
clock_t lastTime = 0;
GLuint projectionMatrixUniformLocation;
GLuint viewMatrixUniformLocation;
GLuint modelMatrixUniformLocation;
GLuint bufferIDs[3] = {0};
GLuint shaderIDs[3] = {0};
Matrix projectionMatrix;
Matrix viewMatrix;
Matrix modelMatrix;

void initialize(int, char *[]);
void initWindow(int, char *[]);
void resizeFunction(int, int);
void renderFunction(void);
void timerFunction(int);
void idleFunction(void);
void createCube(void);
void destroyCube(void);
void drawCube(void);

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
	glGetError();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	exitOnGLError("ERROR: Could not set OpenGl depth testing options");
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	exitOnGLError("ERROR: Could not set OpenGL culling options");
	modelMatrix = IDENTITY_MATRIX;
	projectionMatrix = IDENTITY_MATRIX;
	viewMatrix = IDENTITY_MATRIX;
	translateMatrix(&viewMatrix, 0, 0, -2);
	createCube();
	return;
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
	glutCloseFunc(destroyCube);
	return;
}

void resizeFunction(int width, int height) {
	currentWidth = width;
	currentHeight = height;
	glViewport(0, 0, currentWidth, currentHeight);
	projectionMatrix = createProjectionMatrix(60,
			(float)currentWidth/currentHeight, 1.0f, 100.0f);
	glUseProgram(shaderIDs[0]);
	glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, projectionMatrix.m);
	glUseProgram(0);
	return;
}

void renderFunction(void) {
	frameCount++;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawCube();
	glutSwapBuffers();
	glutPostRedisplay();
	return;
}

void idleFunction(void) {
	glutPostRedisplay();
	return;
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
	return;
}

void createCube(void) {
	const Vertex vertices[8] = {
		{{-0.5f, -0.5f,  0.5f, 1}, {0, 0, 1, 1}},
		{{-0.5f,  0.5f,  0.5f, 1}, {1, 0, 0, 1}},
		{{ 0.5f,  0.5f,  0.5f, 1}, {0, 1, 0, 1}},
		{{ 0.5f, -0.5f,  0.5f, 1}, {1, 1, 0, 1}},
		{{-0.5f, -0.5f, -0.5f, 1}, {1, 1, 1, 1}},
		{{-0.5f,  0.5f, -0.5f, 1}, {1, 0, 0, 1}},
		{{ 0.5f,  0.5f, -0.5f, 1}, {1, 0, 1, 1}},
		{{ 0.5f, -0.5f, -0.5f, 1}, {0, 0, 1, 1}},
	};
	const GLuint indices[36] = {
		0, 2, 1, 0, 3, 2,
		4, 3, 0, 4, 7, 3,
		4, 1, 5, 4, 0, 1,
		3, 6, 2, 3, 7, 6,
		1, 6, 5, 1, 2, 6,
		7, 5, 6, 7, 4, 5
	};
	/* create a shader program */
	shaderIDs[0] = glCreateProgram();
	exitOnGLError("ERROR: Could not create the shader program");
	/* load, attach, and link shader programs */
	shaderIDs[1] = loadShader("simpleShader.fragment.glsl", GL_FRAGMENT_SHADER);
	shaderIDs[2] = loadShader("simpleShader.vertex.glsl", GL_VERTEX_SHADER);
	glAttachShader(shaderIDs[0], shaderIDs[1]);
	glAttachShader(shaderIDs[0], shaderIDs[2]);
	glLinkProgram(shaderIDs[0]);
	exitOnGLError("Error: Could not link the shader program");
	/* retrieve shader uniforms */
	modelMatrixUniformLocation = glGetUniformLocation(shaderIDs[0], "modelMatrix");
	viewMatrixUniformLocation = glGetUniformLocation(shaderIDs[0], "viewMatrix");
	projectionMatrixUniformLocation = glGetUniformLocation(shaderIDs[0], "projectionMatrix");
	exitOnGLError("Error: Could not get the shader uniform locations");
	/* generate buffers */
	glGenBuffers(2, &bufferIDs[1]);
	exitOnGLError("Error: Could not generate the buffer objects");
	/* generate and bind vertex array objects */
	glGenVertexArrays(1, &bufferIDs[0]);
	exitOnGLError("Error: Could not generate the VAO");
	glBindVertexArray(bufferIDs[0]);
	exitOnGLError("Error: Could not bind the VAO");
	/* enable vertex attribute locations */
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	exitOnGLError("Error: Could not enable vertex attributes");
	/* insert VBO binding, data uploading, and vertex attribute descriptions */
	glBindBuffer(GL_ARRAY_BUFFER, bufferIDs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);
	exitOnGLError("Error: Could not bind the VBO to the VAO");
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof *vertices, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof *vertices, (GLvoid *)sizeof vertices[0].position);
	/* insert IBO binding and uploading code */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIDs[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);
	exitOnGLError("Error: Could not bind the IBO to the VAO");
	glBindVertexArray(0);
	return;
}

void destroyCube(void) {
	/* delete shaders */
	glDetachShader(shaderIDs[0], shaderIDs[1]);
	glDetachShader(shaderIDs[0], shaderIDs[2]);
	glDeleteShader(shaderIDs[1]);
	glDeleteShader(shaderIDs[2]);
	glDeleteProgram(shaderIDs[0]);
	exitOnGLError("Error: Could not destroy the shaders");
	/* delete VBOs and VAOs */
	glDeleteBuffers(2, &bufferIDs[1]);
	glDeleteVertexArrays(1, &bufferIDs[0]);
	exitOnGLError("Error: Could not destroy the buffer objects");
	return;
}

void drawCube(void) {
	/* rotations are based on program time */
	float cubeAngle;
	clock_t now = clock();
	if (lastTime == 0) {
		lastTime = now;
	}
	cubeRotation += 45.0f*(8.0f*(float)(now - lastTime)/CLOCKS_PER_SEC);
	cubeAngle = degreesToRadians(cubeRotation);
	lastTime = now;
	/* transform the matrix */
	modelMatrix = IDENTITY_MATRIX;
	rotateAboutY(&modelMatrix, cubeAngle);
	rotateAboutX(&modelMatrix, cubeAngle);
	/* shader calls */
	glUseProgram(shaderIDs[0]);
	exitOnGLError("ERROR: Could not use the shader program");
	glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, modelMatrix.m);
	glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, viewMatrix.m);
	exitOnGLError("ERROR: Could not set the shader uniforms");
	/* drawing */
	glBindVertexArray(bufferIDs[0]);
	exitOnGLError("ERROR: Could not bind the VAO for drawing purposes");
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
	exitOnGLError("ERROR: Could not draw the cube");
	glBindVertexArray(0);
	glUseProgram(0);
	return;
}
