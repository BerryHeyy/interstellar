#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Model.h"
#include "Window.h"

class Game
{
private:
	// Time
	float deltaTime;
	float lastFrame;

	std::vector<Model*> models;

	void renderModels();

public:
	// Window
	Window window;

	Camera playerCamera;

	Game(int width, int height);

	bool shouldGameClose();

	void gameLoop();

	void processInput();
	void updateCamera();
};