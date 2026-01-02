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

		m_ImGuiLayer = new ImGuiLayer();
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

		m_RenderDevice->Start(m_Specification.windowSpec.width, m_Specification.windowSpec.height, m_Window->getNativeWindowHandle());

		BAS_EN_INFO("Running OnInitialLoad for all attached layers");

		for (const std::unique_ptr<Layer>& layer : m_LayerStack) {
			layer->OnInitialLoad();
		}

		m_ImGuiLayer->OnInitialLoad();

		while (m_Running) {
			glfwPollEvents();

			if (glfwWindowShouldClose(m_Window->getGLFWWindow())) {
				stop();
				break;
			}

			float currentTime = getTime();
			float timestep = std::clamp(currentTime - lastTime, 0.001f, 0.1f);
			lastTime = currentTime;

			if (!m_Minimized) {

				for (const std::unique_ptr<Layer>& layer : m_LayerStack) {
					layer->OnUpdate(timestep);
				}

				for (const std::unique_ptr<Layer>& layer : m_LayerStack) {
					layer->OnRender();
				}

				m_ImGuiLayer->Begin();

				for (const std::unique_ptr<Layer>& layer : m_LayerStack) {
					layer->OnImGuiRender();
				}

				m_ImGuiLayer->End();
			}

			bgfx::frame();
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

	void Application::onResize(uint32_t width, uint32_t height) {

		if (width && height == 0) m_Minimized = true;

		for (const std::unique_ptr<Layer>& layer : m_LayerStack) {
			layer->OnResize(width, height);
		}
	}
}