#pragma once

#include "Window.h"
#include "Layer.h"
#include "Rendering/RenderDevice.h"
#include "ImGui/ImGuiLayer.h"

#include <memory>
#include <vector>

namespace Basen{
	struct ApplicationSpecification {
		std::string name = "Application";
		WindowSpecification windowSpec;
	};

	class Application {
	public:
		Application(const ApplicationSpecification& spec = ApplicationSpecification());
		~Application();

		void run();
		void stop();

		template<typename TLayer>
		requires(std::is_base_of_v<Layer, TLayer>)
		void PushLayer() {
			m_LayerStack.push_back(std::make_unique<TLayer>());
		}

		static Application& get();

		std::shared_ptr<Window> getWindow() const {
			return m_Window;
		}

		RenderDevice* getRenderDevice() { return m_RenderDevice.get(); }

		float getTime();

		void onResize(uint32_t width, uint32_t height); //Temporary, use event system at some point
	private:
		ApplicationSpecification m_Specification;
		std::shared_ptr<Window> m_Window;
		
		std::unique_ptr<RenderDevice> m_RenderDevice;

		bool m_Running = false;
		bool m_Minimized = false;

		std::vector<std::unique_ptr<Layer>> m_LayerStack;

		ImGuiLayer* m_ImGuiLayer;
	};
}