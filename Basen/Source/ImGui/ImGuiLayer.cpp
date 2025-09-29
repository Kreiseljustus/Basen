#include "ImGuiLayer.h"

#include "Core/Application.h"

#include "bgfx-imgui/src/imgui_impl_bgfx.h"
#include "imgui.h"

#include <backends/imgui_impl_glfw.h>

#include "Core/Logging.h"

namespace Basen {

	static ImGuiLayer* s_Instance = nullptr;

	ImGuiLayer::~ImGuiLayer() {

	}

	void ImGuiLayer::OnInitialLoad() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		s_Instance = this;

		GLFWwindow* window = Application::get().getWindow()->getGLFWWindow();

		glfwSetScrollCallback(Application::get().getWindow()->getGLFWWindow(), [](GLFWwindow* window, double xoffset, double yoffset) {
			if (s_Instance)
				s_Instance->scroll_callback(window, xoffset, yoffset);
		});

		ImGui_ImplGlfw_InitForOther(window, true);
		ImGui_ImplBgfx_Init(1, [](ImGuiViewport* vp) -> void* { return nullptr; });

		BAS_EN_INFO("Initialized ImGui");
	}

	void ImGuiLayer::Begin() {
		GLFWwindow* window = Application::get().getWindow()->getGLFWWindow();

		ImGui_ImplBgfx_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End() {
		m_MouseWheel = 0;

		ImGui::Render();

		//I want the editor to render the current scene into a texture and display it using imgui
		//but currently this is a work around as its not implemented yet
		ImGui_ImplBgfx_Render(1, ImGui::GetDrawData(), 0);
	}

	void ImGuiLayer::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		m_MouseWheel += (float)yoffset;
	}
}