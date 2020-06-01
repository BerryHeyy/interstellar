#include <fstream>
#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Camera.h"
#include "Window.h"
#include "Game.h"
#include "Material.h"
#include "Mesh.h"
#include "Primitives.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const GLint WIDTH = 800, HEIGHT = 600;

Game game(WIDTH, HEIGHT);

void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main()
{

	// Shader init
	Shader lightingShader("vertex_shader.glsl", "lighting_fragment.glsl");

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Primitives
	Mesh mesh0(&primitive::Triangle());
	mesh0.rotate(glm::vec3(0.0f, 40.0f, 0.0f));

	// Materials
	Material material0(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f));
	
	// Lights
	glm::vec3 lightPos0(0.0f, 0.0f, 1.0f);
	
	// Game Loop
	while (!game.shouldGameClose())
	{
		

		// Input
		game.processInput();
		game.gameLoop();

		// Render
		glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Shading
		lightingShader.use();
		lightingShader.setVec3("lightPos0", lightPos0);
		lightingShader.setVec3("cameraPos", game.playerCamera.Position);

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(game.playerCamera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = game.playerCamera.GetViewMatrix();
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);

		mesh0.render(&lightingShader);

		// Other stuff
		glfwSwapBuffers(game.window.window);
		glFlush();
		glfwPollEvents();

	}

	// Deallocate memory
	lightingShader.deleteShader();
	glfwTerminate();

	return EXIT_SUCCESS;
}