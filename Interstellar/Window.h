#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.h"


class Window
{
private:
	void createWindow(int height, int width);
	void initCallbacks();

	static void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH);
	static void mouse_callback(GLFWwindow* windoww, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* windoww, double xoffset, double yoffset);

public:

	bool initSuccess = false;
	GLFWwindow* window;

	Window();
	Window(int width, int height);
	
	
	
};