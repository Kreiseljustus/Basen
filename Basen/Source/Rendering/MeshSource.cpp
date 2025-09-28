#include "MeshSource.h"
#include <fstream>
#include <sstream>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

MeshSource::MeshSource(const std::string& filepath)
    : m_FilePath(filepath)
{
    LoadFromFile();
}

bool MeshSource::LoadFromFile() {
    std::ifstream file(m_FilePath);
    if (!file.is_open()) return false;

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(m_FilePath,
        aiProcess_Triangulate |
        aiProcess_GenSmoothNormals |
        aiProcess_FlipUVs |
        aiProcess_JoinIdenticalVertices |
    aiProcess_FlipWindingOrder);

    if (!scene || !scene->HasMeshes()) {
        return false;
    }

    aiMesh* mesh = scene->mMeshes[0];

    m_Vertices.clear();
    m_Indices.clear();

    for (size_t i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex{};

        vertex.position[0] = mesh->mVertices[i].x;
        vertex.position[1] = mesh->mVertices[i].y;
        vertex.position[2] = mesh->mVertices[i].z;

        if (mesh->HasNormals()) {
            vertex.normal[0] = mesh->mNormals[i].x;
            vertex.normal[1] = mesh->mNormals[i].y;
            vertex.normal[2] = mesh->mNormals[i].z;
        }
        else {
            vertex.normal[0] = vertex.normal[1] = vertex.normal[2] = 0.0f;
        }

        //TODO: add support for more uvs
        /*if (mesh->HasTextureCoords(0)) {
            vertex.texcoord[0] = mesh->mTextureCoords[0][i].x;
            vertex.texcoord[1] = mesh->mTextureCoords[0][i].y;
        }
        else {
            vertex.texcoord[0] = vertex.texcoord[1] = 0.0f;
        }*/
        
        m_Vertices.emplace_back(vertex);
    }

    for (size_t i = 0; i < mesh->mNumFaces; i++) {
        const aiFace& face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++) {
            m_Indices.emplace_back(static_cast<uint16_t>(face.mIndices[j]));
        }
    }
 
    return true;
}