#pragma once

#include "Core/Layer.h"

#include <GLFW/glfw3.h>

namespace Basen {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer() : m_MouseWheel(0) {};
		~ImGuiLayer();

		virtual void OnInitialLoad() override;
		
		void Begin();
		void End();
	private:
		float m_MouseWheel; //TEMP

		void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};
}

