#include "utils.h"

const Matrix IDENTITY_MATRIX = {
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	}
};

float cotangent(float angle) {
	return (float)(1.0 / tan(angle));
}

float degreesToRadians(float degrees) {
	return degrees * (float)(PI / 180);
}

float radiansToDegrees(float radians) {
	return radians * (float)(180 / PI);
}

Matrix multiplyMatrices(const Matrix* m1, const Matrix* m2) {
	Matrix out = IDENTITY_MATRIX;
	unsigned int row, column, row_offset;
	for (row = 0, row_offset = row * 4; row < 4; ++row, row_offset = row * 4) {
		for (column = 0; column < 4; ++column) {
			out.m[row_offset + column] =
				(m1->m[row_offset + 0] * m2->m[column + 0]) +
				(m1->m[row_offset + 1] * m2->m[column + 4]) +
				(m1->m[row_offset + 2] * m2->m[column + 8]) +
				(m1->m[row_offset + 3] * m2->m[column + 12]);
		}
	}
	return out;
}

void scaleMatrix(Matrix* m, float x, float y, float z) {
	Matrix scale = IDENTITY_MATRIX;
	scale.m[0] = x;
	scale.m[5] = y;
	scale.m[10] = z;
	memcpy(m->m, multiplyMatrices(m, &scale).m, sizeof(m->m));
}

void translateMatrix(Matrix* m, float x, float y, float z) {
	Matrix translation = IDENTITY_MATRIX;
	translation.m[12] = x;
	translation.m[13] = y;
	translation.m[14] = z;
	memcpy(m->m, multiplyMatrices(m, &translation).m, sizeof(m->m));
}

void rotateAboutX(Matrix* m, float angle) {
	Matrix rotation = IDENTITY_MATRIX;
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);
	rotation.m[5] = cosine;
	rotation.m[6] = -sine;
	rotation.m[9] = sine;
	rotation.m[10] = cosine;
	memcpy(m->m, multiplyMatrices(m, &rotation).m, sizeof(m->m));
}

void rotateAboutY(Matrix* m, float angle) {
	Matrix rotation = IDENTITY_MATRIX;
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);
	rotation.m[0] = cosine;
	rotation.m[8] = sine;
	rotation.m[2] = -sine;
	rotation.m[10] = cosine;
	memcpy(m->m, multiplyMatrices(m, &rotation).m, sizeof(m->m));
}

void rotateAboutZ(Matrix* m, float angle) {
	Matrix rotation = IDENTITY_MATRIX;
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);
	rotation.m[0] = cosine;
	rotation.m[1] = -sine;
	rotation.m[4] = sine;
	rotation.m[5] = cosine;
	memcpy(m->m, multiplyMatrices(m, &rotation).m, sizeof(m->m));
}

Matrix createProjectionMatrix(float fovy, float aspect_ratio, float near_plane,
		float far_plane) {
	Matrix out = { { 0 } };
	const float y_scale = cotangent(degreesToRadians(fovy / 2));
	const float x_scale = y_scale / aspect_ratio;
	const float frustum_length = far_plane - near_plane;
	out.m[0] = x_scale;
	out.m[5] = y_scale;
	out.m[10] = -((far_plane + near_plane) / frustum_length);
	out.m[11] = -1;
	out.m[14] = -((2 * near_plane * far_plane) / frustum_length);
	return out;
}

void exitOnGLError(const char* error_message) {
	const GLenum errorValue = glGetError();
	if (errorValue != GL_NO_ERROR) {
		fprintf(stderr, "%s: %s\n", error_message, gluErrorString(errorValue));
		exit(EXIT_FAILURE);
	}
}

GLuint loadShader(const char* filename, GLenum shader_type) {
	GLuint shader_id = 0;
	FILE *file;
	long file_size = -1;
	GLchar *glsl_source;
	if (NULL != (file = fopen(filename, "rb")) &&
			0 == fseek(file, 0, SEEK_END) &&
			-1 != (file_size = ftell(file))) {
		rewind(file);
		if (NULL != (glsl_source = (char*)malloc(file_size + 1))) {
			if (file_size == (long)fread(glsl_source, sizeof(char), file_size, file)) {
				glsl_source[file_size] = '\0';
				if (0 != (shader_id = glCreateShader(shader_type))) {
					glShaderSource(shader_id, 1, (const GLchar * const *)&glsl_source, NULL);
					glCompileShader(shader_id);
					exitOnGLError("Could not compile a shader");
				}
				else {
					fprintf(stderr, "ERROR: Could not create a shader.\n");
				}
			}
			else {
				fprintf(stderr, "ERROR: Could not read file %s\n", filename);
			}
			free(glsl_source);
		}
		else {
			fprintf(stderr, "ERROR: Could not allocate %li bytes.\n", file_size);
		}
		fclose(file);
	}
	else {
		if (NULL != file) {
			fclose(file);
		}
		fprintf(stderr, "ERROR: Could not open file %s\n", filename);
	}
	return shader_id;
}
