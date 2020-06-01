#include "Game.hpp"

Game::Game(int width, int height) 
{
	this->window = Window(width, height);
	this->playerCamera = Camera(glm::vec3(0.0f, 0.0f, 1.0f));
}

void Game::renderModels()
{
	for (int i = 0; i < this->models.size(); i++)
	{
		this->models.at(i)->render();
	}
}

bool Game::shouldGameClose()
{
	return glfwWindowShouldClose(this->window.window);
}

void Game::gameLoop()
{
	// Time
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	
	// Input
	this->processInput();
	this->updateCamera();

	this->renderModels();

}

void Game::processInput()
{
	if (glfwGetKey(this->window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(this->window.window, true);

	if (glfwGetKey(this->window.window, GLFW_KEY_W) == GLFW_PRESS)
		playerCamera.processKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(this->window.window, GLFW_KEY_S) == GLFW_PRESS)
		playerCamera.processKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(this->window.window, GLFW_KEY_A) == GLFW_PRESS)
		playerCamera.processKeyboard(LEFT, deltaTime);
	if (glfwGetKey(this->window.window, GLFW_KEY_D) == GLFW_PRESS)
		playerCamera.processKeyboard(RIGHT, deltaTime);

	if (glfwGetKey(this->window.window, GLFW_KEY_R) == GLFW_PRESS)
		playerCamera.processKeyboard(UP, deltaTime);
	if (glfwGetKey(this->window.window, GLFW_KEY_F) == GLFW_PRESS)
		playerCamera.processKeyboard(DOWN, deltaTime);
}

void Game::updateCamera()
{
	playerCamera.processMouseCallback();
	playerCamera.processMouseMovement();
	playerCamera.processMouseScroll();
}
