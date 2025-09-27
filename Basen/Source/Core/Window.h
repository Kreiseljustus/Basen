#pragma once

#include <string>

#include <glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw3native.h>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace Basen {

	struct WindowSpecification {
		std::string title;
		uint32_t width = 1280;
		uint32_t height = 720;
		bool isResizeable = true;
		bool vsync = true;
	};

	class Window {
	public:
		Window(const WindowSpecification& specs = WindowSpecification());
		~Window();

		void initializeWindow();

		void onResize(int width, int height);

		int getWidth() { return m_Spec.width; }
		int getHeight() { return m_Spec.height; }
		std::string_view getTitle() { return m_Spec.title; }

		GLFWwindow* getGLFWWindow() { return m_Window; }

#ifdef _WIN32
		HWND getNativeWindow() { return glfwGetWin32Window(m_Window); } //TODO: support all platforms in a single method (templates?)
#endif

	private:
		WindowSpecification m_Spec;

		GLFWwindow* m_Window;
	};
}