#pragma once
#include "gl_math.h"

struct obj {
	vec3 pos;
	vec3 size;
};

int OBJ_collisionCheck(struct obj* a, struct obj* b);