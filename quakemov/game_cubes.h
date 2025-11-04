#pragma once
#include "gl.h"
#include "game_obj.h"

struct cube {
	struct obj obj;
	int solid;
	mesh* mesh; //this is just temporal
};

#define MAX_CUBES 512
extern struct cube cubes[MAX_CUBES];
extern int cubes_count;

int CUBES_addCube(struct cube cube);
int CUBES_removeIndex(int index);
void CUBES_clear();