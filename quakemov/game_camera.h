#pragma once
#include <GLFW/glfw3.h>
#include "gl_math.h"

struct camera {
	vec3 pos;
	vec3 rot;
	int mouseLock;
};

struct camera* CAMERA_getCamera();
mat4 CAMERA_toMatrix();

void CAMERA_setCamera(vec3 pos, vec3 rot);

//this is only for when camera is in free mode, ie not attached to a player entity
void CAMERA_handleInput(GLFWwindow* window);

#define CAMERA_FREE 0
#define CAMERA_PLAYER 1