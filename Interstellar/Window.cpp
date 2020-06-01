#include "Window.h"

double Camera::newX;
double Camera::newY;

bool Camera::firstMouse;
double Camera::scrollYOffset;

Window::Window()
{
	this->createWindow(800, 600);
}

Window::Window(int width, int height)
{
	this->createWindow(width, height);
}

void Window::createWindow(int width, int height)
{
	glfwInit();

	// Set Window options
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(width, height, "Interstellar", nullptr, nullptr);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		initSuccess = false;
	}

	glfwMakeContextCurrent(window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;

	// Initate GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialze GLEW" << std::endl;


		initSuccess = false;
	}

	// Define viewport dimensions
	glViewport(0, 0, screenWidth, screenHeight);

	glEnable(GL_DEPTH_TEST);

	// Initialize window callbacks

	this->initCallbacks();

	initSuccess = true;
}

void Window::framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
}

void Window::mouse_callback(GLFWwindow* windoww, double xpos, double ypos)
{
	Camera::newX = xpos;
	Camera::newY = ypos;
}

void Window::scroll_callback(GLFWwindow* windoww, double xoffset, double yoffset)
{
	Camera::scrollYOffset = yoffset;
}

void Window::initCallbacks()
{
	glfwSetFramebufferSizeCallback(this->window, this->framebuffer_resize_callback);
	glfwSetCursorPosCallback(this->window, this->mouse_callback);
	glfwSetScrollCallback(this->window, this->scroll_callback);
}