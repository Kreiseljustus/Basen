#include <imgui.h>

#include "AppLayer.h"

#include <Core/Logging.h>

#include <bx/math.h>

//This layer is currently mainly used to debug and test stuff

AppLayer::AppLayer() {
	
}

AppLayer::~AppLayer()
{
}

void AppLayer::OnInitialLoad() {
	if (!m_TestMeshSource.LoadFromFile() && !m_Test2MeshSource.LoadFromFile()) {
		BAS_APP_WARN("Failed to load test mesh source!");
	}

	m_TestMesh = new StaticMesh{ m_TestMeshSource };
	m_Test2Mesh = new StaticMesh{ m_Test2MeshSource };

	m_MeshShader.Load();

	m_ShaderProgram = m_MeshShader.GetHandle();

	m_ColorTex = bgfx::createTexture2D(1280, 720, false, 1, bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_RT | BGFX_TEXTURE_BLIT_DST);
	
	m_DepthTex = bgfx::createTexture2D(1280, 720, false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT_WRITE_ONLY);

	bgfx::TextureHandle fbTextures[] = { m_ColorTex, m_DepthTex };

	m_FrameBufferTex = bgfx::createFrameBuffer(BX_COUNTOF(fbTextures), fbTextures, true);

	uint32_t testTexData[4] = {
		0xFF0000FF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFF0000FF
	};

	m_TestTexture = bgfx::createTexture2D(2, 2, false, 1, bgfx::TextureFormat::RGBA8, 0, bgfx::copy(testTexData, sizeof(testTexData)));

	m_SampleTex = bgfx::createTexture2D(1280, 720, false, 1, bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_BLIT_DST);
}


void AppLayer::OnImGuiRender() {
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;

	bool dummy = false;

	ImGuiWindowFlags dwindow_flags =
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_NoBackground;

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 0.0f;
	style.WindowBorderSize = 0.0f;
	style.WindowPadding = ImVec2(0,0);

	ImGui::Begin("MainDockSpace", nullptr, dwindow_flags);

	ImGui::PopStyleVar(2);

	ImGuiID dockspace_id = ImGui::GetID("dockspace");

	ImGui::DockSpace(dockspace_id, ImVec2(0,0), ImGuiDockNodeFlags_None);

	ImGui::End();

	ImGui::Begin("Editor", &dummy, window_flags);

	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Import model", "Ctrl+I")) {
				BAS_APP_INFO("Clicked import model");
			}
			if (ImGui::MenuItem("Swap test model")) {
				m_RenderSecondMesh = !m_RenderSecondMesh;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::DragFloat("Angle", &angle);
	ImGui::DragFloat3("Eye", &m_Eye.x);

	ImGui::End();

	ImGui::Begin("Viewport");
	ImVec2 viewportSize = ImGui::GetContentRegionAvail();
	ImTextureID viewTexId = (ImTextureID)(uintptr_t)m_SampleTex.idx;
	ImGui::Image(viewTexId, viewportSize, ImVec2(0, 0), ImVec2(1, 1));

	ImGui::End();
}

void AppLayer::OnUpdate(float ts) {

}

void AppLayer::OnRender() {

	bgfx::setState(BGFX_STATE_MSAA | BGFX_STATE_DEFAULT | BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_WRITE_Z | BGFX_STATE_WRITE_B | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_G | BGFX_STATE_WRITE_R | BGFX_STATE_CULL_CCW);

	float view[16];
	float proj[16];

	float rotation[16];

	float translation[16];
	float temp[16];

	const bx::Vec3 at = { 0.0f,0.0f,0.0f };

	angle += 0.01f;

	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x10000, 1.0f, 0);

	bx::mtxLookAt(view, m_Eye, at);

	bgfx::setViewFrameBuffer(1, m_FrameBufferTex);

	bgfx::setViewRect(1, 0, 0, 1280, 720);

	bgfx::setViewClear(1, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x100000, 1.0f, 0);

	float aspect = float(1280) / float(720);
	bx::mtxProj(proj, 60.0f, aspect, 0.01f, 50.0f, bgfx::getCaps()->homogeneousDepth);

	bgfx::setViewTransform(1, view, proj);

	bgfx::touch(1);

	//bx::mtxRotateX(rotation, angle);

	for (int i = 0; i < 1; i++) {

		bx::mtxTranslate(translation, (float) -i, 0, (float) -i);
		//bx::mtxMul(temp, translation, rotation);

		if (m_RenderSecondMesh) {
			bx::mtxRotateZYX(rotation, angle, angle, angle);
			
			bx::mtxMul(temp, translation, rotation);

			bgfx::setTransform(temp);
			m_Test2Mesh->Render(m_ShaderProgram, 1);
		}
		else {
			bx::mtxRotateX(rotation, angle);
			bx::mtxMul(temp, translation, rotation);

			bgfx::setTransform(temp);
			m_TestMesh->Render(m_ShaderProgram, 1);
		}
	}

	bgfx::dbgTextClear();
	bgfx::dbgTextPrintf(0, 0, 0x4F, "BGFX RENDERING OK");

	bgfx::blit(0, m_SampleTex, 0, 0, m_ColorTex, 0, 0, 1280, 720);
}

void AppLayer::OnResize(uint32_t width, uint32_t height) {

	if (width == 0 && height == 0) return;

	BAS_APP_INFO("Resize with {0} and {1}", width, height);

    if (bgfx::isValid(m_ColorTex)) {
        bgfx::destroy(m_ColorTex);
        m_ColorTex = BGFX_INVALID_HANDLE;
    }
    if (bgfx::isValid(m_DepthTex)) {
        bgfx::destroy(m_DepthTex);
        m_DepthTex = BGFX_INVALID_HANDLE;
    }
    if (bgfx::isValid(m_FrameBufferTex)) {
        bgfx::destroy(m_FrameBufferTex);
        m_FrameBufferTex = BGFX_INVALID_HANDLE;
    }
    if (bgfx::isValid(m_SampleTex)) {
        bgfx::destroy(m_SampleTex);
        m_SampleTex = BGFX_INVALID_HANDLE;
    }

    m_ColorTex = bgfx::createTexture2D(width, height, false, 1, bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_RT | BGFX_TEXTURE_BLIT_DST);
    m_DepthTex = bgfx::createTexture2D(width, height, false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT_WRITE_ONLY);
    bgfx::TextureHandle fbTextures[] = { m_ColorTex, m_DepthTex };
    m_FrameBufferTex = bgfx::createFrameBuffer(BX_COUNTOF(fbTextures), fbTextures, true);
    m_SampleTex = bgfx::createTexture2D(width, height, false, 1, bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_BLIT_DST);
}
