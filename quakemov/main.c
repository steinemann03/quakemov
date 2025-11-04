/*
saw yt video about quake movement and wanted to try to implement that lol
i guess next move is to move collision to detecting triangle meshes instead of aabb boxes
would also be nice to create a proper render pipeline
not to proud of how things depend on each other
main code is also kinda of an eye sore
*/

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
//
#include "gl.h"
#include "gl_shaders.h"
#include "gl_helper.h"
//
#include "game_camera.h"
#include "game_cubes.h"
#include "game_player.h"

int RANDOM_int(int min, int max) {
	return min + rand() % (max - min + 1);
}

//main program
void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s..", description);
}
int is_scrolling = 0;
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	is_scrolling = 1;
}

void key_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (glfwGetKey(window, GLFW_KEY_F1))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_F2))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void simplegen() {
	//floor
	{
		struct obj test_obj = {
			{0,0,0},
			{100,1,100}
		};
		struct cube test_cube = {
			test_obj,
			1,
			NULL
		};
		CUBES_addCube(test_cube);
	}

	//random floating cubes
	for (int i = 0; i < 516; i++) {
		float s = RANDOM_int(5, 20);
		struct obj o = {
			{ RANDOM_int(-200,200), RANDOM_int(0, 1000), RANDOM_int(-200,200) },
			{ s,s,s }
		};
		struct cube c = {
			o,
			1,
			NULL
		};
		CUBES_addCube(c);
	}
}

int main() {
	srand(time(NULL));

	glfwSetErrorCallback(error_callback);
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, "quake movement", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwSetScrollCallback(window, scroll_callback);

	GLuint mesh_program = uGL_CompileProgram(mesh_vert, mesh_frag);
	GLuint text_program = uGL_CompileProgram(text_vert, text_frag);

	GLuint text_texture = uGL_LoadTexture("text.png");
	GLuint tile_texture = uGL_LoadTexture("tile_texture.png");

	//generate world cubes
	simplegen();

	//get pointers
	int camera_isAttached;
	struct camera* camera_ptr = CAMERA_getCamera();
	struct player* player_ptr = PLAYER_getPlayer();
	camera_isAttached = CAMERA_PLAYER;
	
	PLAYER_reset();

	int width, height; float ratio;
	double time;
	glfwSwapInterval(1);
	while (!glfwWindowShouldClose(window)) {
		glfwGetFramebufferSize(window, &width, &height);
		ratio = (float)width / (float)height;
		time = glfwGetTime();

		//input logic
		key_input(window);

		if (glfwGetKey(window, GLFW_KEY_ENTER)) {
			CUBES_clear();
			simplegen();
		}

		switch (camera_isAttached) {
		case CAMERA_PLAYER:
			PLAYER_handleInput(window);
			//
			if (is_scrolling) {
				PLAYER_forceJump();
				is_scrolling = 0;
			}
			if (glfwGetKey(window, GLFW_KEY_F))
				PLAYER_launch(1);
			//
			CAMERA_setCamera(player_ptr->obj.pos, player_ptr->rot);
			camera_ptr->pos.f[1] += player_ptr->obj.size.f[1];
			break;
		case CAMERA_FREE:
		default:
			CAMERA_handleInput(window);
			break;
		}

		//game logic pipeline
		PLAYER_physLogic();

		//render pipeline
		{
			glViewport(0, 0, width, height);
			glClearColor(0.1, 0.2, 0.3, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		{
			glEnable(GL_DEPTH_TEST);
			glUseProgram(mesh_program);
			glActiveTexture(GL_TEXTURE0);
			
			float player_speed = sqrtf(player_ptr->vel.f[0] * player_ptr->vel.f[0] + player_ptr->vel.f[2] * player_ptr->vel.f[2]);
			mat4 projection = matrix_perspective(70.f + player_speed * 2, ratio, 0.1f, 10000.f);
			hGL_bindMat4(mesh_program, "projection", projection);

			mat4 view = CAMERA_toMatrix();
			hGL_bindMat4(mesh_program, "view", view);

			{
				glBindTexture(GL_TEXTURE_2D, tile_texture);
				glUniform1i(glGetUniformLocation(mesh_program, "texture1"), 0);

				mat4 model = matrix_identity();
				hGL_bindMat4(mesh_program, "model", model);

				for (int i = 0; i < cubes_count; i++) {
					glBindVertexArray(cubes[i].mesh->VAO);
					glDrawArrays(GL_TRIANGLES, 0, cubes[i].mesh->size);
				}
			}

			{
				//coordinate text
				char* x_buffer[16];
				char* y_buffer[16];
				char* z_buffer[16];
				char* pitch_buffer[16];
				char* yaw_buffer[16];
				int x_len = snprintf(x_buffer, sizeof(x_buffer), "%.2f", camera_ptr->pos.f[0]);
				int y_len = snprintf(y_buffer, sizeof(x_buffer), "%.2f", camera_ptr->pos.f[1]);
				int z_len = snprintf(z_buffer, sizeof(x_buffer), "%.2f", camera_ptr->pos.f[2]);
				int pitch_len = snprintf(pitch_buffer, sizeof(pitch_buffer), "%.2f", camera_ptr->rot.f[1] * (180 / PI));
				int yaw_len = snprintf(yaw_buffer, sizeof(yaw_buffer), "%.2f", camera_ptr->rot.f[0] * (180 / PI));
				float tpos[2] = { 32, height - 32 }, tsize[2] = { 16,16 };
				float tcolor[3] = { 1,1,1 };
				tGL_TextRender(tpos, tsize, tcolor, x_buffer, x_len, width, height, text_program, text_texture);
				tpos[1] -= 16;
				tGL_TextRender(tpos, tsize, tcolor, y_buffer, y_len, width, height, text_program, text_texture);
				tpos[1] -= 16;
				tGL_TextRender(tpos, tsize, tcolor, z_buffer, z_len, width, height, text_program, text_texture);
				tpos[1] -= 16;
				tcolor[0] = 0.5; tcolor[2] = 0.5;
				tGL_TextRender(tpos, tsize, tcolor, pitch_buffer, pitch_len, width, height, text_program, text_texture);
				tpos[1] -= 16;
				tGL_TextRender(tpos, tsize, tcolor, yaw_buffer, yaw_len, width, height, text_program, text_texture);
				tpos[1] -= 16;
				
				float player_speed = sqrtf(player_ptr->vel.f[0] * player_ptr->vel.f[0] + player_ptr->vel.f[2] * player_ptr->vel.f[2]);
				char* speed_buffer[16];
				int speed_len = (snprintf(speed_buffer, sizeof(speed_buffer), "%.1f", player_speed));
				float spos[2] = { (width / 2) - (16 * speed_len) / 2, 64 };
				float ssize[2] = { 32,32 };
				float scolor[3] = { 1,1,0 };
				tGL_TextRender(spos, ssize, scolor, speed_buffer, speed_len, width, height, text_program, text_texture);
			}

			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(mesh_program);
	glDeleteProgram(text_program);

	CUBES_clear();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}