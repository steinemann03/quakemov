#include "game_camera.h"

struct camera camera = { 0 };

struct camera* CAMERA_getCamera(){
	return &camera;
}

mat4 CAMERA_toMatrix(){
	mat4 matrix = matrix_identity();
	matrix = matrix_translate(matrix, vector_negate(camera.pos));
	matrix = matrix_rotate(matrix, (vec4) { 0, 1, 0, camera.rot.f[1] });
	matrix = matrix_rotate(matrix, (vec4) { 1, 0, 0, camera.rot.f[0] });
	return matrix;
}

void CAMERA_setCamera(vec3 pos, vec3 rot){
	camera.pos = pos;
	camera.rot = rot;
}

#define MOVE_STR 2.f
#define ROT_STR 0.001f
void CAMERA_handleInput(GLFWwindow* window){

	static int HOME_PRESSED = 0;
	if (glfwGetKey(window, GLFW_KEY_HOME)) {
		if (!HOME_PRESSED)
			camera.mouseLock = !camera.mouseLock;
		HOME_PRESSED = 1;
	}
	else
		HOME_PRESSED = 0;

	if (glfwGetKey(window, GLFW_KEY_W)) {
		camera.pos.f[0] += cosf(camera.rot.f[0]) * sinf(camera.rot.f[1]) * -MOVE_STR;
		camera.pos.f[1] += sinf(-camera.rot.f[0]) * -MOVE_STR;
		camera.pos.f[2] += cosf(camera.rot.f[0]) * cosf(camera.rot.f[1]) * -MOVE_STR;
	}
	if (glfwGetKey(window, GLFW_KEY_S)) {
		camera.pos.f[0] += cosf(camera.rot.f[0]) * sinf(camera.rot.f[1]) * MOVE_STR;
		camera.pos.f[1] += sinf(-camera.rot.f[0]) * MOVE_STR;
		camera.pos.f[2] += cosf(camera.rot.f[0]) * cosf(camera.rot.f[1]) * MOVE_STR;
	}

	if (camera.mouseLock) {
		double xpos, ypos;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		glfwGetCursorPos(window, &xpos, &ypos);
		glfwSetCursorPos(window, (float)width / 2, (float)height / 2);

		xpos = (xpos - (width / 2));
		ypos = (ypos - (height / 2));
		camera.rot.f[1] -= xpos * ROT_STR;
		camera.rot.f[0] -= ypos * ROT_STR;

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	} else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
