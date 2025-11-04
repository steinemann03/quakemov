#include "game_player.h"

struct player player = { 0 };

struct player* PLAYER_getPlayer() {
	return &player;
}

#define PLAYER_WIDTH 4
#define PLAYER_HEIGHT 8
void PLAYER_reset() {
	player.obj.pos = (vec3){ 0,16,0 };
	player.obj.size = (vec3){ PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_WIDTH };
	player.rot = (vec3){ 0,0,0 };
	player.vel = (vec3){ 0,0,0 };
	player.f = 0;
	//
	//player.mouseLock = 0;
}

/*

void PLAYER_addVelocity(vec3 velocity) {
	player.vel = vector_combine(player.vel, velocity);
}

//
#define lol 5
#define jump_str 4.f
void player_jump() {
	if (player.f < lol) {
		player.vel.f[1] = jump_str;
		player.f = lol;
	}
}
//

#define move_str 1.f
#define rot_str 0.005f
void PLAYER_handleInput(GLFWwindow* window) {
	static int HOME_PRESSED = 0;
	if (glfwGetKey(window, GLFW_KEY_HOME)) {
		if (!HOME_PRESSED)
			player.mouseLock = !player.mouseLock;
		HOME_PRESSED = 1;
	}
	else
		HOME_PRESSED = 0;

	if (player.mouseLock) {
		double xpos, ypos;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		glfwGetCursorPos(window, &xpos, &ypos);
		glfwSetCursorPos(window, (float)width / 2, (float)height / 2);

		xpos = (xpos - (width / 2));
		ypos = (ypos - (height / 2));
		player.rot.f[1] -= xpos * rot_str;
		player.rot.f[0] -= ypos * rot_str;

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	if (glfwGetKey(window, GLFW_KEY_SPACE))
		player_jump();

	if (glfwGetKey(window, GLFW_KEY_W)) {
		player.vel.f[0] += sinf(player.rot.f[1]) * -move_str;
		player.vel.f[2] += cosf(player.rot.f[1]) * -move_str;
	}
	if (glfwGetKey(window, GLFW_KEY_S)) {
		player.vel.f[0] += sinf(player.rot.f[1]) * move_str;
		player.vel.f[2] += cosf(player.rot.f[1]) * move_str;
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		player.vel.f[0] += sinf(player.rot.f[1] + 1.5708f) * move_str;
		player.vel.f[2] += cosf(player.rot.f[1] + 1.5708f) * move_str;
	}
	if (glfwGetKey(window, GLFW_KEY_A)) {
		player.vel.f[0] += sinf(player.rot.f[1] - 1.5708f) * move_str;
		player.vel.f[2] += cosf(player.rot.f[1] - 1.5708f) * move_str;
	}
}

#define PLAYER_GRAV 0.1f
void PLAYER_physLogic() {
	player.vel.f[1] -= PLAYER_GRAV;
	player.f++;

	player.obj.pos.f[1] += player.vel.f[1];
	for (int i = 0; i < cubes_count; i++) {
		if (!cubes[i].solid)
			continue;
		if (OBJ_collisionCheck(&player.obj, &cubes[i].obj)) {
			if (player.vel.f[1] < 0) {
				player.f = 0;
			}
			player.obj.pos.f[1] -= player.vel.f[1];
			player.vel.f[1] = 0;
		}
	}

	player.obj.pos.f[0] += player.vel.f[0];
	for (int i = 0; i < cubes_count; i++) {
		if (!cubes[i].solid)
			continue;
		if (OBJ_collisionCheck(&player.obj, &cubes[i].obj)) {
			player.obj.pos.f[0] -= player.vel.f[0];
			player.vel.f[0] = 0;
		}
	}

	player.obj.pos.f[2] += player.vel.f[2];
	for (int i = 0; i < cubes_count; i++) {
		if (!cubes[i].solid)
			continue;
		if (OBJ_collisionCheck(&player.obj, &cubes[i].obj)) {
			player.obj.pos.f[2] -= player.vel.f[2];
			player.vel.f[2] = 0;
		}
	}

	if (player.f < lol) {
		player.vel.f[0] *= 0.5f;
		player.vel.f[2] *= 0.5f;
	}
	else {
		player.vel.f[0] *= 0.7f;
		player.vel.f[2] *= 0.7f;
	}
	
	if (player.obj.pos.f[1] < -512.f) {
		PLAYER_reset();
	}
}
*/

vec3 accelerate(vec3 vel, vec3 wishdir, float wishspeed, float accel, float maxspeed) {
	float currentspeed = vector_dot(vel, wishdir);
	float addspeed = wishspeed - currentspeed;
	if (addspeed <= 0)
		return vel;

	float accelspeed = accel * wishspeed;
	if (accelspeed > addspeed)
		accelspeed = addspeed;

	vel.f[0] += accelspeed * wishdir.f[0];
	vel.f[2] += accelspeed * wishdir.f[2];

	float speed = sqrtf(vel.f[0] * vel.f[0] + vel.f[2] * vel.f[2]);
	if (speed > maxspeed) {
		float scale = maxspeed / speed;
		vel.f[0] *= scale;
		vel.f[2] *= scale;
	}
	return vel;
}

#define JUMP_STR 2.5f
#define JUMP_THRESHOLD 5

#define GROUND_ACCELERATION 0.25f
#define AIR_ACCELERATION 0.15f
#define GROUND_FRICTION 16.0f
#define AIR_FRICTION 0.1f

#define MOVE_SPEED 0.8f
#define MAX_SPEED 600.0f
#define GRAV_FORCE 0.1f

#define DELTA_RATE 0.016f

void player_jump() {
	if (player.f < JUMP_THRESHOLD) {
		player.vel.f[1] = JUMP_STR;
		player.f = JUMP_THRESHOLD;
	}
}

//global source variable that 2 functions use
//
vec3 p_wishdir = { 0 };
void PLAYER_handleInput(GLFWwindow* window) {
	static int HOME_PRESSED = 0;
	if (glfwGetKey(window, GLFW_KEY_HOME)) {
		if (!HOME_PRESSED)
			player.mouseLock = !player.mouseLock;
		HOME_PRESSED = 1;
	}
	else HOME_PRESSED = 0;

	static int DEL_PRESSED = 0;
	if (glfwGetKey(window, GLFW_KEY_DELETE)) {
		if (!DEL_PRESSED)
			player.ghost = !player.ghost;
		DEL_PRESSED = 1;
	}
	else DEL_PRESSED = 0;

	if (player.mouseLock) {
		double xpos, ypos;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glfwGetCursorPos(window, &xpos, &ypos);
		glfwSetCursorPos(window, (float)width / 2, (float)height / 2);

		xpos -= (width / 2);
		ypos -= (height / 2);
		player.rot.f[1] -= xpos * 0.005f;
		player.rot.f[0] -= ypos * 0.005f;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	p_wishdir = (vec3){ 0 };
	if (glfwGetKey(window, GLFW_KEY_W)) {
		p_wishdir.f[0] += sinf(player.rot.f[1]) * -1;
		p_wishdir.f[2] += cosf(player.rot.f[1]) * -1;
	}
	if (glfwGetKey(window, GLFW_KEY_S)) {
		p_wishdir.f[0] += sinf(player.rot.f[1]);
		p_wishdir.f[2] += cosf(player.rot.f[1]);
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		p_wishdir.f[0] += sinf(player.rot.f[1] + 1.5708f);
		p_wishdir.f[2] += cosf(player.rot.f[1] + 1.5708f);
	}
	if (glfwGetKey(window, GLFW_KEY_A)) {
		p_wishdir.f[0] += sinf(player.rot.f[1] - 1.5708f);
		p_wishdir.f[2] += cosf(player.rot.f[1] - 1.5708f);
	}
	p_wishdir = vector_normalize(p_wishdir);

	if (glfwGetKey(window, GLFW_KEY_SPACE))
		player_jump();
}

void PLAYER_forceJump(){
	player_jump();
}

void PLAYER_launch(float str){
	player.vel.f[0] += cosf(player.rot.f[0]) * sinf(player.rot.f[1]) * -str;
	player.vel.f[1] += sinf(-player.rot.f[0]) * -str;
	player.vel.f[2] += cosf(player.rot.f[0]) * cosf(player.rot.f[1]) * -str;
}

void PLAYER_physLogic() {
	player.vel.f[1] -= GRAV_FORCE;
	player.f++;

	float speed = sqrtf(player.vel.f[0] * player.vel.f[0] + player.vel.f[2] * player.vel.f[2]);
	if (speed > 0) {
		float friction;
		if (player.f <= 1)
			friction = GROUND_FRICTION;
		else
			friction = AIR_FRICTION;
		float drop = speed * friction * DELTA_RATE;
		float newspeed_ratio = fmaxf(speed - drop, 0.0f) / speed;
		player.vel.f[0] *= newspeed_ratio;
		player.vel.f[2] *= newspeed_ratio;
	}

	float acceleration;
	if (player.f <= 1)
		acceleration = GROUND_ACCELERATION;
	else
		acceleration = AIR_ACCELERATION;
	float wishspeed = (player.f <= 1) ? MOVE_SPEED * 3 : MOVE_SPEED;
	player.vel = accelerate(player.vel, p_wishdir, wishspeed, acceleration, MAX_SPEED);

	for (int i = 0; i < 3; i++) {
		player.obj.pos.f[i] += player.vel.f[i];
		for (int j = 0; j < cubes_count; j++) {
			if (!cubes[j].solid)
				continue;
			if (OBJ_collisionCheck(&player.obj, &cubes[j].obj)) {
				if (i == 1 && player.vel.f[i] < 0)
					player.f = 0;
				player.obj.pos.f[i] -= player.vel.f[i];
				player.vel.f[i] = 0;
			}
		}
	}

	if (player.obj.pos.f[1] < -512.f)
		PLAYER_reset();
}