#pragma once
#include "gl.h"
#include "gl_math.h"

/*
struct camera {
	vec3 pos;
	vec3 rot;
	int mlock;
};
*/

void hGL_bindMat4(GLuint program, char* parram, mat4 mat);

void hGL_CreateCube(vertex* buffer, int s_index, vec3 p, vec4 c, vec3 s, vec4 t);

//mat4 hGL_CamToMat(struct camera* camera);