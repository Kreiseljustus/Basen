#include "StaticMesh.h"
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <iostream>
#include <Core/Logging.h>

static bgfx::VertexLayout s_Layout;

StaticMesh::StaticMesh(const MeshSource& source) {
    if (s_Layout.getStride() == 0) {

        BAS_EN_INFO("Vertexlayout not defined, creating with pos3float, texcoord02float");

        s_Layout
            .begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Normal,   3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::TexCoord0,2, bgfx::AttribType::Float)
            .end();
    }

    m_VertexBuffer = bgfx::createVertexBuffer(
        bgfx::makeRef(source.GetVertices().data(), static_cast<uint32_t>(sizeof(Vertex)) * static_cast<uint32_t>(source.GetVertices().size())),
        s_Layout
    );

    m_IndexBuffer = bgfx::createIndexBuffer(
        bgfx::makeRef(source.GetIndices().data(), static_cast<uint32_t>(sizeof(uint16_t)) * static_cast<uint32_t>(source.GetIndices().size()))
    );

    m_IndexCount = static_cast<uint32_t>(source.GetIndices().size());
}

StaticMesh::~StaticMesh() {
    if (bgfx::isValid(m_VertexBuffer)) bgfx::destroy(m_VertexBuffer);
    if (bgfx::isValid(m_IndexBuffer)) bgfx::destroy(m_IndexBuffer);
}

void StaticMesh::Render(bgfx::ProgramHandle program, bgfx::ViewId viewId) {

    if (!bgfx::isValid(m_VertexBuffer)) { BAS_EN_ERROR("Vertex buffer invalid!"); }
    if (!bgfx::isValid(m_IndexBuffer)) { BAS_EN_ERROR("Index buffer invalid!"); }

    bgfx::setVertexBuffer(0, m_VertexBuffer);
    bgfx::setIndexBuffer(m_IndexBuffer);
    bgfx::submit(viewId, program);
}