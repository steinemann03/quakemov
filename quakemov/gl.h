#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

GLuint uGL_CompileProgram(char* vert_source, char* frag_source);
GLuint uGL_LoadTexture(const char* file);

typedef struct {
	float x, y, z;
	float r, g, b, a;
	float u, v;
}vertex;

typedef struct {
	float x, y;
	float u, v;
}vertex_text;

typedef struct {
	GLuint VAO;
	GLuint VBO;
	int size;
	int isTranslucent;
}mesh;

void uGL_SetupMesh(mesh* mesh, int size, int isTranslucent);
void uGL_UpdateMesh(mesh* mesh, vertex* data, int size);