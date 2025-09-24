#pragma once

#include <string>
#include <bgfx/bgfx.h>

namespace Basen {

	enum ShaderType {
		Fragment,
		Vertex
	};

	class Shader {
	public:
		Shader(const std::string_view shaderName);

		void Load();
		inline bgfx::ProgramHandle GetHandle() { return m_Handle; }
	private:
		bgfx::ShaderHandle loadShader(const ShaderType type);
		bgfx::ProgramHandle loadProgram();
	private:
		bool m_Loaded{ false };

		std::string_view m_ShaderName{};

		bgfx::ProgramHandle m_Handle{};
	};
}