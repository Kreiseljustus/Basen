#include "Application.h"

#include <algorithm>

#include "Logging.h"

namespace Basen {
	static Application* s_Application = nullptr;

	Application::Application(const ApplicationSpecification& specs) : m_Specification(specs) {
		s_Application = this;

		if (m_Specification.windowSpec.title.empty()) m_Specification.windowSpec.title = m_Specification.name;

		m_Window = std::make_shared<Window>(m_Specification.windowSpec);

		m_RenderDevice = std::make_unique<RenderDevice>();
	}

	Application::~Application() {
		m_Window->~Window();

		glfwTerminate();
		
		s_Application = nullptr;
	}

	void Application::run() {
		m_Running = true;

		float lastTime = getTime();

		Basen::Logging::Init();

		m_RenderDevice->Start(m_Specification.windowSpec.width, m_Specification.windowSpec.height, m_Window->getNativeWindow());

		BAS_EN_INFO("Running OnInitialLoad for all attached layers");

		for (const std::unique_ptr<Layer>& layer : m_LayerStack) {
			layer->OnInitialLoad();
		}

		while (m_Running) {
			glfwPollEvents();

			if (glfwWindowShouldClose(m_Window->getGLFWWindow())) {
				stop();
				break;
			}

			float currentTime = getTime();
			float timestep = std::clamp(currentTime - lastTime, 0.001f, 0.1f);
			lastTime = currentTime;

			for (const std::unique_ptr<Layer>& layer : m_LayerStack) {
				layer->OnUpdate(timestep);
			}

			for (const std::unique_ptr<Layer>& layer : m_LayerStack) {
				layer->OnRender();
			}
		}
	}

	void Application::stop() {
		m_Running = false;
	}

	Application& Application::get() {
		if (s_Application) {
			return *s_Application;
		}
	}

	float Application::getTime() {
		return (float)glfwGetTime();
	}
}