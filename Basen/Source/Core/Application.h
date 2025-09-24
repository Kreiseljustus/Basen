#pragma once

#include <vector>
#include <string>

#include "Window.h"
#include "Layer.h"

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

		static Application& get();,
	private:
		ApplicationSpecification m_Specification;
		std::shared_ptr<Window> m_Window;
		bool m_Running = false;

		std::vector<std::unique_ptr<Layer>> m_LayerStack;
	};
}