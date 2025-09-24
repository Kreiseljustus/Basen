#include <imgui.h>

#include <bx/bx.h>
#include <bx/math.h>

#include "Basen.h"
#include "Core/Window.h"
#include "Rendering/RenderDevice.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Rendering/MeshSource.h"
#include "Rendering/StaticMesh.h"

#include "Rendering/Shader.h"

int main()
{
	Basen::Init();

	Basen::Window w(Basen::WindowSpecification{.title = "Hallo"});
	Basen::RenderDevice device{};

	device.Start(800, 800, w.getNativeWindow());

	MeshSource source{ "assets/test1.fbx" };

	if (!source.LoadFromFile()) {
		std::cout << "Failed to load source model" << std::endl;
	}

	StaticMesh mesh{ source };

	Basen::Shader shader("mesh");

	shader.Load();

	bgfx::ProgramHandle handle = shader.GetHandle();

	//bgfx::UniformHandle u_modelViewProjHandle = bgfx::createUniform("u_mvp", bgfx::UniformType::Mat4);

	bgfx::setState(BGFX_STATE_MSAA | BGFX_STATE_DEFAULT | BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_WRITE_Z | BGFX_STATE_WRITE_B | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_G | BGFX_STATE_WRITE_R | BGFX_STATE_CULL_CCW );

	float angle = 0.0f;

	float view[16];
	float proj[16];

	float model[16];
	float rotation[16];

	float translation[16];
	float temp[16];

	const bx::Vec3 at = { 0.0f,0.0f,0.0f };
	const bx::Vec3 eye = { -0.0f,0.0f,-5.0f };

	while (!glfwWindowShouldClose(w.getGLFWWindow())) {
		glfwPollEvents();

		angle += 0.01;
		
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000, 1.0f, 0);
	
		//bgfx::setDebug(BGFX_DEBUG_WIREFRAME);

			bx::mtxLookAt(view, eye, at);

			float aspect = float(800) / float(800);
			bx::mtxProj(proj, 60.0f, aspect, 0.01f, 50.0f, bgfx::getCaps()->homogeneousDepth);

			bgfx::setViewRect(0, 0, 0, uint16_t(800), uint16_t(800));

			bgfx::setViewTransform(0, view, proj);

			bgfx::touch(0);

			bx::mtxRotateX(rotation, angle);

			for (int i = 0; i < 1; i++) {

				bx::mtxTranslate(translation, -i, 0, -i);

				bx::mtxMul(temp, translation, rotation);

				bgfx::setTransform(temp);
				mesh.Render(handle);
			}

			//bgfx::setUniform(u_modelViewProjHandle, mvp);
		

		//mesh.Render(handle);

		bgfx::frame();
	}
}