#include "Window.h"

Basen::Window::Window(const WindowSpecification& spec) : m_Spec(spec) {
	initializeWindow();
}

Basen::Window::~Window() {

}

void Basen::Window::initializeWindow() {
	if (!glfwInit()) {
		std::println(std::cout, "Failed to initialize glfw!");
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); //Disable OpenGL so bgfx can render

	m_Window = glfwCreateWindow(m_Spec.width, m_Spec.height, m_Spec.title.data(), NULL, NULL);

	if (!m_Window) {
		glfwTerminate();
		std::println(std::cout, "Failed to create glfw window!");
	}
}

void Basen::Window::onResize(int width, int height) {

}
