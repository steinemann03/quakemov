#pragma once
#include "gl.h"

void tGL_TextRender(
	float pos[2], float size[2], float color[3],
	char* txt, int len,
	int screen_width, int screen_height,
	GLuint program, GLuint font_texture
);