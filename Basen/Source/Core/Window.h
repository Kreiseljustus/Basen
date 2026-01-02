#pragma once

#include <string>

#ifdef WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elifdef LINUX
#define GLFW_EXPOSE_NATIVE_X11
#endif

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "Core/NativeWindowHandle.h"

namespace Basen {

	struct WindowSpecification {
		std::string title;
		uint32_t width = 1280;
		uint32_t height = 720;
		bool isResizable = true;
		bool vsync = true;
	};

	class Window {
	public:
		Window(const WindowSpecification& specs = WindowSpecification());
		~Window();

		void initializeWindow();

		void onResize(uint32_t width, uint32_t height);

		int getWidth() const { return m_Spec.width; }
		int getHeight() const { return m_Spec.height; }
		std::string_view getTitle() { return m_Spec.title; }

		GLFWwindow* getGLFWWindow() { return m_Window; }

		NativeWindowHandle getNativeWindowHandle() const;
	private:
		WindowSpecification m_Spec;

		GLFWwindow* m_Window;
	};
}