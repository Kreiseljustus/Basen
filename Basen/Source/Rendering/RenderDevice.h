#pragma once

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <Windows.h>

#include <stdexcept>

namespace Basen {
	class RenderDevice {
	public:
		void Start(uint32_t width, uint32_t height, HWND windowHandle);
		void Resize(uint32_t width, uint32_t height);
		void Shutdown();
	private:
		bgfx::Init m_BGFXInit{};

		HWND m_WindowHandle{ nullptr };
	};
}