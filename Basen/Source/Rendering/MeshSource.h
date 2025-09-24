#pragma once
#include <vector>
#include <string>
#include <cstdint>

struct Vertex {
    float position[3];
    //float normal[3];
    //float texcoord[2];
};

class MeshSource {
public:
    MeshSource(const std::string& filepath);

    const std::vector<Vertex>& GetVertices() const { return m_Vertices; }
    const std::vector<uint16_t>& GetIndices() const { return m_Indices; }
    const std::string& GetFilePath() const { return m_FilePath; }

    bool LoadFromFile();

private:
    std::string m_FilePath;
    std::vector<Vertex> m_Vertices;
    std::vector<uint16_t> m_Indices;
};