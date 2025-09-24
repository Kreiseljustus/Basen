#include "Window.h"

Basen::Window::Window(const std::string_view title, uint32_t width, uint32_t height) : m_Title(title), m_Width(width), m_Height(height) {
	initializeWindow();
}

void Basen::Window::initializeWindow() {
	if (!glfwInit()) {
		std::println(std::cout, "Failed to initialize glfw!");
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); //Disable OpenGL so bgfx can render

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.data(), NULL, NULL);

	if (!m_Window) {
		glfwTerminate();
		std::println(std::cout, "Failed to create glfw window!");
	}
}

void Basen::Window::onResize(int width, int height) {

}
