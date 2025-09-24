#include "Shader.h"

#include <iostream>
#include <fstream>
#include <vector>

Basen::Shader::Shader(const std::string_view shaderName) : m_ShaderName(shaderName) {

}

void Basen::Shader::Load() {
	m_Handle = loadProgram();
}

bgfx::ShaderHandle Basen::Shader::loadShader(const ShaderType type) {
	std::string shaderPath = std::string("assets/shaders/") + (type == ShaderType::Fragment ? "fs_" : "vs_")
		+ m_ShaderName.data() + std::string("_");

	switch (bgfx::getRendererType()) {
	case bgfx::RendererType::Noop:
	case bgfx::RendererType::Direct3D11: shaderPath += "dx11"; break;
	case bgfx::RendererType::Direct3D12: shaderPath += "dx12"; break;
	case bgfx::RendererType::Gnm: shaderPath += "UNIMPLEMENTED AS OF NOW: THIS WILL THROW AN ERROR"; break;
	case bgfx::RendererType::Metal: shaderPath += "mtl"; break;
	case bgfx::RendererType::OpenGL: shaderPath += "gl"; break;
	case bgfx::RendererType::OpenGLES: shaderPath += "gl"; break; //Probably not correct!
	case bgfx::RendererType::Vulkan: shaderPath += "vk"; break;
	default: throw std::exception("Failed to load shader because the renderer is not supported");
	}

	shaderPath += ".bin";

	std::ifstream shaderFile(shaderPath, std::ios::binary | std::ios::ate);

	if (!shaderFile.is_open()) {
		//Log error
		std::cout << "Failed to open file: " << shaderPath << std::endl;
	}

	std::streamsize fileSize = shaderFile.tellg();
	shaderFile.seekg(0, std::ios::beg);

	std::vector<uint8_t> buffer(fileSize + 1);
	
	if (!shaderFile.read(reinterpret_cast<char*>(buffer.data()), fileSize)) {
		//Log error
		std::cout << "Failed to read file: " << shaderPath << std::endl;
	}
	buffer[fileSize] = '\0';

	const bgfx::Memory* mem = bgfx::copy(buffer.data(), static_cast<uint32_t>(buffer.size()));
	
	return bgfx::createShader(mem);
}

bgfx::ProgramHandle Basen::Shader::loadProgram() {
	bgfx::ShaderHandle vsh = loadShader(ShaderType::Vertex);
	bgfx::ShaderHandle fsh = loadShader(ShaderType::Fragment);

	bgfx::ProgramHandle program = bgfx::createProgram(vsh, fsh, true);

	if (!bgfx::isValid(program)) {
		//Log error
		std::cout << "Shader program invalid" << std::endl;
	}

	std::cout << "Successfully loaded shader " << m_ShaderName;

	return program;
}
