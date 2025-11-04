#pragma once
//#include <GLFW/glfw3.h>
#include "game_obj.h"

//stupid
#include "game_cubes.h"//i mean tihs could just be included in the source file but it conflicts with glad

struct player {
	struct obj obj;
	vec3 rot;
	vec3 vel;
	int f;
	//
	int mouseLock;
	int ghost;
};

struct player* PLAYER_getPlayer();

void PLAYER_reset();

//void PLAYER_addVelocity(vec3 velocity);

void PLAYER_handleInput(GLFWwindow* window);
void PLAYER_forceJump();
void PLAYER_launch(float str);


void PLAYER_physLogic();
