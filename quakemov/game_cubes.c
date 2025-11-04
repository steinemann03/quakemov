#include "game_cubes.h"

//
#include "gl_helper.h"
//

struct cube cubes[MAX_CUBES] = { 0 };
int cubes_count = 0;


//
void CreateCubeMesh(struct cube* target) {
	target->mesh = malloc(sizeof(mesh));
	uGL_SetupMesh(target->mesh, 36, 0);
	vertex buffer[36] = { 0 };
	vec4 color = { 1,1,1,1 };
	float overal_size = sqrtf(target->obj.size.f[0] * target->obj.size.f[1] * target->obj.size.f[2]);
	vec4 texture = { 0,0,1,1 };
	hGL_CreateCube(&buffer, 0, target->obj.pos, color, target->obj.size, texture);
	uGL_UpdateMesh(target->mesh, &buffer, 36);
}
void DeleteCubeMesh(struct cube* target) {
	mesh* mesh = &target->mesh;
	glDeleteVertexArrays(1, &mesh->VAO);
	glDeleteBuffers(1, &mesh->VBO);
	free(target->mesh);
}
//

int CUBES_addCube(struct cube cube) {
	if (cubes_count >= MAX_CUBES)
		return -1;
	cubes[cubes_count] = cube;

	//
	CreateCubeMesh(&cubes[cubes_count]);
	//

	return cubes_count++;
}

int CUBES_removeIndex(int index) {
	if (index < 0 || index >= cubes_count)
		return -1;
	if (index != cubes_count) {
		cubes[index] = cubes[cubes_count];
	}

	//
	DeleteCubeMesh(&cubes[index]);
	//

	cubes_count--;
}

void CUBES_clear() {
	//
	for (int i = 0; i < cubes_count; i++)
		DeleteCubeMesh(&cubes[i]);
	//
	cubes_count = 0;
}