#pragma once

#include <string>
#include <iostream> //TODO: REMOVE

#include <glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw3native.h>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace Basen {

	class Window {
	public:
		Window(const std::string_view title = "New Window", uint32_t width = 600, uint32_t height = 800);

		void initializeWindow();

		void onResize(int width, int height);

		int getWidth() { return m_Width; }
		int getHeight() { return m_Height; }
		std::string_view getTitle() { return m_Title; }

		GLFWwindow* getGLFWWindow() { return m_Window; }

#ifdef _WIN32
		HWND getNativeWindow() { return glfwGetWin32Window(m_Window); } //TODO: support all platforms in a single method (templates?)
#endif

	private:
		GLFWwindow* m_Window;

		uint32_t m_Width, m_Height;
		const std::string_view m_Title;
	};
}