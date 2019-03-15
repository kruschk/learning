#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

static const struct {
	float x, y;
	float r, g, b;
} vertices[3] = {
	{-0.6f, -0.4f, 1.0f, 0.0f, 0.0f},
	{ 0.6f, -0.4f, 0.0f, 1.0f, 0.0f},
	{ 0.0f,  0.6f, 0.0f, 0.0f, 1.0f}
}



if (!glfwInit()) {
	/* initialization failed */
}

glfwTerminate();

void error_callback(int error, const char description[]) {
	fprintf(stderr, "Error: %s\n", description);
}

glfwSetErrorCallback(error_callback);

/* require OpenGL version 2.0 */
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

GLFWwindow *window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
if (!window) {
	/* Winow or OpenGL context creation failed */
}

glfwDestroyWindow(window);

glfwMakeContextCurrent(window);

while (!glfwWindowShouldClose(window)) {
	/* keep running */
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
		int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

int width, height;
glfwGetFramebufferSize(window, &width, &height);
glViewport(0, 0, width, height);

double time = glfwGetTime();

glfwSwapBuffers(window);

glfwSwapInterval(1);

glfwPollEvents();
