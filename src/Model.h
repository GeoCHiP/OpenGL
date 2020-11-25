#pragma once

#include "Mesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <string>
#include <vector>

class Model {
public:
    Model(const char *filePath) { LoadModel(filePath); }

    void Draw(Shader &shader);

private:
    void LoadModel(const std::string &filePath);
    void ProcessNode(aiNode *node, const aiScene *scene);
    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<TextureInfo> LoadMaterialTextures(aiMaterial *material,
            aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const std::string &fileName, const std::string &filePath);

private:
    std::string m_FileDirectory;
    std::vector<Mesh> m_Meshes;
    std::vector<TextureInfo> m_TexturesLoaded;
};