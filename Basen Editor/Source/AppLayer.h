#pragma once

#include "Core/Layer.h"

#include "Rendering/MeshSource.h"
#include "Rendering/StaticMesh.h"
#include "Rendering/Shader.h"

#include <bgfx/bgfx.h>

class AppLayer : public Basen::Layer {
public: 
	AppLayer();
	virtual ~AppLayer();

	virtual void OnInitialLoad() override;

	virtual void OnImGuiRender() override;
	virtual void OnUpdate(float ts) override;
	virtual void OnRender() override;
private:
	MeshSource m_TestMeshSource{ "assets/test1.fbx" };
	StaticMesh* m_TestMesh;

	Basen::Shader m_MeshShader{ "mesh" };

	bgfx::ProgramHandle m_ShaderProgram;

	float angle{ 0.0f };
};