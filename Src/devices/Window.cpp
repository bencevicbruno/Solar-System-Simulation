#include "devices/Window.h"

#include <iostream>
#include <sstream>

#include "devices/Cursor.h"
#include "devices/Mouse.h"
#include "devices/Keyboard.h"
#include "utils/Utils.h"

Window& Window::GetInstance()
{
	static Window instance("Solar System Simulation");

	return instance;
}

std::string Window::getTitle() const
{
	return title;
}

bool Window::isRunning() const
{
	return running;
}

bool Window::hasCursor() const
{
	return isCursorGrabbed;
}

void Window::update()
{
	glfwSwapBuffers(pWindow);
	glfwPollEvents();
}

void Window::close()
{
	running = false;
}

bool Window::shouldClose() const
{
	return !running
		|| glfwWindowShouldClose(pWindow);
}

void Window::grabCursor()
{
	glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	isCursorGrabbed = true;
}

void Window::releaseCursor()
{
	glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	isCursorGrabbed = false;
}

Matrix Window::getOrthogonalMatrix() const
{
	float near = -1.0f;
	float far = 1.0f;
	float left = 0.0f;
	float right = (float)WIDTH;
	float top = 0.0f;
	float bottom = (float)HEIGHT;

	Matrix matrix = Matrix::GetIdentity();

	matrix.data[0][0] = 2 / (right - left);
	matrix.data[1][1] = 2 / (top - bottom);
	matrix.data[2][2] = -2 / (far - near);

	matrix.data[0][3] = -(right + left) / (right - left);
	matrix.data[1][3] = -(top + bottom) / (top - bottom);
	matrix.data[2][3] = -(far + near) / (far - near);
	matrix.data[3][3] = 1;

	return matrix;
}

Window::Window(std::string title):
	title(title), running(true),
	isCursorGrabbed(false)
{
	initGLFW();

	pWindow = glfwCreateWindow(WIDTH, HEIGHT, title.c_str(), NULL, NULL);
	if (pWindow == nullptr)
	{
		glfwTerminate();
		Utils::CrashWithLog("Failed to create GLFWwindow!");
	}

	glfwMakeContextCurrent(pWindow);

	initGLEW();

	glfwSetFramebufferSizeCallback(pWindow,
		[](GLFWwindow* window, int newWidth, int newHeight) -> void
		{
			glViewport(0, 0, newWidth, newHeight);
		});

	Keyboard::GetInstance().init(pWindow);
	Mouse::GetInstance().init(pWindow);
	Cursor::GetInstance().init(pWindow);
	releaseCursor();
}

Window::~Window()
{
	glfwDestroyWindow(pWindow);
	glfwTerminate();
}

void Window::initGLFW() const
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwSetErrorCallback([](int code, const char* message) -> void
		{
			std::stringstream ss;
			ss << "GLFW #" << code << " " << message << std::endl;

			Utils::CrashWithLog(ss.str());
		}
	);
}

void Window::initGLEW() const
{
	if (glewInit() != GLEW_OK)
	{
		Utils::CrashWithLog("Unable to initialize GLEW!");
	}
}