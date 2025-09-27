#include <imgui.h>

#include "AppLayer.h"

#include <Core/Logging.h>

#include <bx/math.h>

AppLayer::AppLayer() {
	
}

AppLayer::~AppLayer()
{
}

void AppLayer::OnInitialLoad() {
	if (!m_TestMeshSource.LoadFromFile()) {
		BAS_APP_WARN("Failed to load test mesh source!");
	}

	m_TestMesh = new StaticMesh{ m_TestMeshSource };

	m_MeshShader.Load();

	m_ShaderProgram = m_MeshShader.GetHandle();

	bgfx::setState(BGFX_STATE_MSAA | BGFX_STATE_DEFAULT | BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_WRITE_Z | BGFX_STATE_WRITE_B | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_G | BGFX_STATE_WRITE_R | BGFX_STATE_CULL_CCW);
}


void AppLayer::OnUpdate(float ts) {

}

void AppLayer::OnRender() {
	float view[16];
	float proj[16];

	float rotation[16];

	float translation[16];
	float temp[16];

	const bx::Vec3 at = { 0.0f,0.0f,0.0f };
	const bx::Vec3 eye = { -0.0f,0.0f,-5.0f };

	angle += 0.01f;

	bx::mtxLookAt(view, eye, at);

	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000, 1.0f, 0);

	float aspect = float(1280) / float(720);
	bx::mtxProj(proj, 60.0f, aspect, 0.01f, 50.0f, bgfx::getCaps()->homogeneousDepth);

	bgfx::setViewRect(0, 0, 0, uint16_t(1280), uint16_t(720));

	bgfx::setViewTransform(0, view, proj);

	bgfx::touch(0);

	bx::mtxRotateX(rotation, angle);

	for (int i = 0; i < 1; i++) {

		bx::mtxTranslate(translation, (float) -i, 0, (float) -i);
		bx::mtxMul(temp, translation, rotation);

		bgfx::setTransform(temp);
		m_TestMesh->Render(m_ShaderProgram);
	}

	bgfx::frame();
}
