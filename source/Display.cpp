#include "Display.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void Display::create(const ContextAttri& context)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, context.major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, context.minor);
	if (context.bProfileCore) {
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	mWindow = glfwCreateWindow(mDisplayMode.width, mDisplayMode.height, title.data(), nullptr, nullptr);
	if (!mWindow) {
		std::cout << "create window failed." << std::endl;
		return;
	}
	glfwMakeContextCurrent(mWindow);

	if (!gladLoadGL()) {
		std::cout << "glad init error." << std::endl;
		destroy();
		return;
	}

	glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);
}

void Display::update()
{
	glfwPollEvents();
	glfwSwapBuffers(mWindow);
	processEvent();
}

void Display::destroy()
{
	glfwDestroyWindow(mWindow);
	glfwTerminate();
	mWindow = nullptr;
}

bool Display::isRequestClosed() const
{
	return glfwWindowShouldClose(mWindow);
}

bool Display::isKeyPressed(unsigned int keyCode) const
{
	return glfwGetKey(mWindow, keyCode) == GLFW_PRESS;
}

void Display::setTitle(const std::string& _title)
{
	title = _title;
}

void Display::setDisplayMode(const DisplayMode& displayMode)
{
	mDisplayMode = displayMode;
}

void Display::frameBufferSizeCallback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

void Display::processEvent()
{
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(mWindow, true);
	}
}
