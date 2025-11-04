#include "gl_text.h"
//
//#include "gl_math.h"
#include "gl_helper.h"
#include <stdio.h>
#include <string.h>

void localGetChar(char letter, int* c0, int* c1) {
	switch (letter) {
	case '1':
		*c0 = 0;
		*c1 = 7;
		break;
	case '2':
		*c0 = 1;
		*c1 = 7;
		break;
	case '3':
		*c0 = 2;
		*c1 = 7;
		break;
	case '4':
		*c0 = 3;
		*c1 = 7;
		break;
	case '5':
		*c0 = 4;
		*c1 = 7;
		break;
	case '6':
		*c0 = 5;
		*c1 = 7;
		break;
	case '7':
		*c0 = 6;
		*c1 = 7;
		break;
	case '8':
		*c0 = 7;
		*c1 = 7;
		break;
	case '9':
		*c0 = 0;
		*c1 = 6;
		break;
	case '0':
		*c0 = 1;
		*c1 = 6;
		break;
		//
	case '=':
		*c0 = 2;
		*c1 = 6;
		break;
	case '-':
		*c0 = 3;
		*c1 = 6;
		break;
	case '+':
		*c0 = 4;
		*c1 = 6;
		break;
	case '/':
		*c0 = 5;
		*c1 = 6;
		break;
	case '*':
		*c0 = 6;
		*c1 = 6;
		break;
	case 'a':
	case 'A':
		*c0 = 0;
		*c1 = 5;
		break;
	case 'b':
	case 'B':
		*c0 = 1;
		*c1 = 5;
		break;
	case 'c':
	case 'C':
		*c0 = 2;
		*c1 = 5;
		break;
	case 'd':
	case 'D':
		*c0 = 3;
		*c1 = 5;
		break;
	case 'e':
	case 'E':
		*c0 = 4;
		*c1 = 5;
		break;
	case 'f':
	case 'F':
		*c0 = 5;
		*c1 = 5;
		break;
	case 'g':
	case 'G':
		*c0 = 6;
		*c1 = 5;
		break;
	case 'h':
	case 'H':
		*c0 = 7;
		*c1 = 5;
		break;
	case 'i':
	case 'I':
		*c0 = 0;
		*c1 = 4;
		break;
	case 'j':
	case 'J':
		*c0 = 1;
		*c1 = 4;
		break;
	case 'k':
	case 'K':
		*c0 = 2;
		*c1 = 4;
		break;
	case 'l':
	case 'L':
		*c0 = 3;
		*c1 = 4;
		break;
	case 'm':
	case 'M':
		*c0 = 4;
		*c1 = 4;
		break;
	case 'n':
	case 'N':
		*c0 = 5;
		*c1 = 4;
		break;
	case 'o':
	case 'O':
		*c0 = 6;
		*c1 = 4;
		break;
	case 'p':
	case 'P':
		*c0 = 7;
		*c1 = 4;
		break;
	case 'q':
	case 'Q':
		*c0 = 0;
		*c1 = 3;
		break;
	case 'r':
	case 'R':
		*c0 = 1;
		*c1 = 3;
		break;
	case 's':
	case 'S':
		*c0 = 2;
		*c1 = 3;
		break;
	case 't':
	case 'T':
		*c0 = 3;
		*c1 = 3;
		break;
	case 'u':
	case 'U':
		*c0 = 4;
		*c1 = 3;
		break;
	case 'v':
	case 'V':
		*c0 = 5;
		*c1 = 3;
		break;
	case 'w':
	case 'W':
		*c0 = 6;
		*c1 = 3;
		break;
	case 'x':
	case 'X':
		*c0 = 0;
		*c1 = 2;
		break;
	case 'y':
	case 'Y':
		*c0 = 1;
		*c1 = 2;
		break;
	case 'z':
	case 'Z':
		*c0 = 2;
		*c1 = 2;
		break;
	case '.':
		*c0 = 0;
		*c1 = 1;
		break;
	case ':':
		*c0 = 1;
		*c1 = 1;
		break;
	case '!':
		*c0 = 2;
		*c1 = 1;
		break;
	case '?':
	default:
		*c0 = 3;
		*c1 = 1;
		break;
	}
}

void tGL_TextRender(
	float pos[2], float size[2], float color[3],
	char* txt, int len,
	int screen_width, int screen_height,
	GLuint program, GLuint font_texture
) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_DEPTH_TEST);
	glUseProgram(program);

	int max_vert = 6 * len;
	GLuint hudVAO, hudVBO;
	glGenVertexArrays(1, &hudVAO);
	glGenBuffers(1, &hudVBO);

	glBindVertexArray(hudVAO);
	glBindBuffer(GL_ARRAY_BUFFER, hudVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_text) * max_vert, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_text), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_text), (void*)(2 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	int vertex_count = 0;
	vertex_text* buffer = malloc(sizeof(vertex_text) * max_vert);
	for (int i = 0; i < len; i++)
	{
		float x = pos[0], y = pos[1];
		float w = size[0], h = size[1];
		x += w * i;

		float cell = 8.0f / 64.0f;
		int cx, cy;
		localGetChar(txt[i], &cx, &cy);

		float u0 = cx * cell;
		float u1 = (cx + 1) * cell;
		float v1 = 1.0f - (cy + 1) * cell;
		float v0 = 1.0f - (cy * cell);

		vertex_text temp_buffer[6] = {
			{x,     y,     u0, v0}, {x + w, y,     u1, v0}, {x,     y + h, u0, v1},
			{x + w,   y,     u1, v0}, {x + w, y + h,   u1, v1}, {x,     y + h, u0, v1}
		};
		memcpy(&buffer[vertex_count], temp_buffer, sizeof(temp_buffer));
		vertex_count += 6;
	}

	mat4 ortho = matrix_ortho(0, screen_width, 0, screen_height, -1, 1);
	hGL_bindMat4(program, "projection", ortho);
	mat4 model = matrix_identity();
	hGL_bindMat4(program, "model", model);

	glUniform4f(glGetUniformLocation(program, "color"), color[0], color[1], color[2], 1.0f);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, font_texture);
	glUniform1i(glGetUniformLocation(program, "hudTexture"), 0);

	glBindBuffer(GL_ARRAY_BUFFER, hudVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_count * sizeof(vertex_text), buffer);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		printf("GL ERROR: %x\n", err);
	}

	glBindVertexArray(hudVAO);
	glDrawArrays(GL_TRIANGLES, 0, vertex_count);

	free(buffer);
	glDeleteVertexArrays(1, &hudVAO);
	glDeleteBuffers(1, &hudVBO);
}