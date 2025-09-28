#include "StaticMesh.h"
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <iostream>

static bgfx::VertexLayout s_Layout;

StaticMesh::StaticMesh(const MeshSource& source) {
    if (s_Layout.getStride() == 0) {
        s_Layout
            .begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Normal,   3, bgfx::AttribType::Float)
            //.add(bgfx::Attrib::TexCoord0,2, bgfx::AttribType::Float)
            .end();
    }

    m_VertexBuffer = bgfx::createVertexBuffer(
        bgfx::makeRef(source.GetVertices().data(), static_cast<uint32_t>(sizeof(Vertex)) * static_cast<uint32_t>(source.GetVertices().size())),
        s_Layout
    );

    std::cout << "Vertices: " << source.GetVertices().size() << std::endl;

    m_IndexBuffer = bgfx::createIndexBuffer(
        bgfx::makeRef(source.GetIndices().data(), static_cast<uint32_t>(sizeof(uint16_t)) * static_cast<uint32_t>(source.GetIndices().size()))
    );

    std::cout << "Indicies: " << source.GetIndices().size() << std::endl;;

    m_IndexCount = static_cast<uint32_t>(source.GetIndices().size());

    std::cout << "Index Count: " << m_IndexCount << std::endl;
}

StaticMesh::~StaticMesh() {
    if (bgfx::isValid(m_VertexBuffer)) bgfx::destroy(m_VertexBuffer);
    if (bgfx::isValid(m_IndexBuffer)) bgfx::destroy(m_IndexBuffer);
}

void StaticMesh::Render(bgfx::ProgramHandle program) {

    if (!bgfx::isValid(m_VertexBuffer)) { std::cout << "vertex buffer invalid" << std::endl; }
    if (!bgfx::isValid(m_IndexBuffer)) { std::cout << "index buffer invalid" << std::endl; }

    bgfx::setVertexBuffer(0, m_VertexBuffer);
    bgfx::setIndexBuffer(m_IndexBuffer);
    bgfx::submit(0, program);
}