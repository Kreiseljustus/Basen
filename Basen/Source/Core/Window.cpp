#include "Window.h"

#include "Logging.h"
#include "Application.h"

Basen::Window::Window(const WindowSpecification& spec) : m_Spec(spec) {
	initializeWindow();
}

Basen::Window::~Window() {

}

void Basen::Window::initializeWindow() {
	if (!glfwInit()) {
		BAS_EN_ERROR("Failed to initialize glfw!");
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); //Disable OpenGL so bgfx can render

	m_Window = glfwCreateWindow(m_Spec.width, m_Spec.height, m_Spec.title.data(), NULL, NULL);

	if (!m_Window) {
		glfwTerminate();
		BAS_EN_ERROR("Failed to create window!");
	}

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {

		Application::get().getWindow()->onResize(width, height);

		});
}

void Basen::Window::onResize(uint32_t width, uint32_t height) {
	m_Spec.width = width;
	m_Spec.height = height;

	Application::get().getRenderDevice()->Resize(width, height);
	
	Application::get().onResize(width, height);
}
