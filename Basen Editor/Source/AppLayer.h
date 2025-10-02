#pragma once

#include "Core/Layer.h"

#include "Rendering/MeshSource.h"
#include "Rendering/StaticMesh.h"
#include "Rendering/Shader.h"

#include <bgfx/bgfx.h>
#include <bx/math.h>

//This layer is currently mainly used to debug and test stuff

class AppLayer : public Basen::Layer {
public: 
	AppLayer();
	virtual ~AppLayer();

	virtual void OnInitialLoad() override;

	virtual void OnImGuiRender() override;
	virtual void OnUpdate(float ts) override;
	virtual void OnRender() override;

	virtual void OnResize(uint32_t width, uint32_t height) override;
private:
	MeshSource m_TestMeshSource{ "assets/test1.fbx" };
	MeshSource m_Test2MeshSource{ "assets/test2.fbx" };

	StaticMesh* m_TestMesh;
	StaticMesh* m_Test2Mesh;

	Basen::Shader m_MeshShader{ "mesh" };

	bgfx::ProgramHandle m_ShaderProgram;

	float angle{ 0.0f };

	bgfx::TextureHandle m_ColorTex;
	bgfx::TextureHandle m_DepthTex;

	bgfx::FrameBufferHandle m_FrameBufferTex;

	bgfx::TextureHandle m_TestTexture;
	bgfx::TextureHandle m_SampleTex;

	bool m_RenderSecondMesh = false;

	bx::Vec3 m_Eye{ -0.0f,0.0f,-5.0f };
};