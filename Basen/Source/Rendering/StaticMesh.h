#pragma once
#include "MeshSource.h"
#include <bgfx/bgfx.h>

class StaticMesh {
public:
    StaticMesh() = default;
    StaticMesh(const MeshSource& source);
    ~StaticMesh();

    void Render(bgfx::ProgramHandle program);

private:
    bgfx::VertexBufferHandle m_VertexBuffer = BGFX_INVALID_HANDLE;
    bgfx::IndexBufferHandle m_IndexBuffer = BGFX_INVALID_HANDLE;
    uint32_t m_IndexCount = 0;
};