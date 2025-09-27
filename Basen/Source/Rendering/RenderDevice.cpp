#include "RenderDevice.h"

#include <iostream>
#include <Core/Logging.h>

void Basen::RenderDevice::Start(uint32_t width, uint32_t height, HWND windowHandle) {

	m_WindowHandle = windowHandle;

	m_BGFXInit.type = bgfx::RendererType::Count;
	m_BGFXInit.resolution.width = width;
	m_BGFXInit.resolution.height = height;
	m_BGFXInit.resolution.reset = BGFX_RESET_VSYNC;

	m_BGFXInit.platformData.nwh = windowHandle;

	if (!bgfx::init(m_BGFXInit)) {
		BAS_EN_CRITICAL("Failed to initialize bgfx!");
	}

	BAS_EN_INFO("Initialized RenderDevice!");

	bgfx::setDebug(BGFX_DEBUG_TEXT);
}

void Basen::RenderDevice::Resize(uint32_t width, uint32_t height) {
	bgfx::reset(width, height, BGFX_RESET_VSYNC);
}

void Basen::RenderDevice::Shutdown() {
	bgfx::shutdown();
}