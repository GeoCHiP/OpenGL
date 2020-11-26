#include "Model.h"
#include "Renderer.h"

#include "stb_image.h"

#include <iostream>

void Model::Draw(Shader &shader) {
    for (int i = 0; i < m_Meshes.size(); ++i)
        m_Meshes[i].Draw(shader);
}

void Model::LoadModel(const std::string &filePath) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "[ERROR]: Assimp:" << importer.GetErrorString() << std::endl;
        return;
    }

    m_FileDirectory = filePath.substr(0, filePath.find_last_of('/'));
    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode *node, const aiScene *scene) {
    for (int i = 0; i < node->mNumMeshes; ++i) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        m_Meshes.push_back(ProcessMesh(mesh, scene));
    }
    for (int i = 0; i < node->mNumChildren; ++i) {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureInfo> textures;

    for (int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;

        glm::vec3 vec;
        vec.x = mesh->mVertices[i].x;
        vec.y = mesh->mVertices[i].y;
        vec.z = mesh->mVertices[i].z;
        vertex.Position = vec;

        vec.x = mesh->mNormals[i].x;
        vec.y = mesh->mNormals[i].y;
        vec.z = mesh->mNormals[i].z;
        vertex.Normal = vec;

        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoord = vec;
        } else {
            vertex.TexCoord = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<TextureInfo> diffuseMaps = LoadMaterialTextures(material,
                                                aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        
        std::vector<TextureInfo> specularMaps = LoadMaterialTextures(material,
                                                aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    for (int i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    return Mesh(vertices, indices, textures);
}

std::vector<TextureInfo> Model::LoadMaterialTextures(aiMaterial *material, aiTextureType type, std::string typeName) {
    std::vector<TextureInfo> textures;
    for (unsigned int i = 0; i < material->GetTextureCount(type); ++i) {
        aiString str;
        material->GetTexture(type, i, &str);
        
        bool skip = false;
        for (unsigned int j = 0; j < m_TexturesLoaded.size(); ++j) {
            if (std::strcmp(m_TexturesLoaded[j].FileName.c_str(), str.C_Str()) == 0) {
                textures.push_back(m_TexturesLoaded[j]);
                skip = true;
                break;
            }
        }

        if (!skip) {
            TextureInfo texture;
            texture.Id = TextureFromFile(str.C_Str(), m_FileDirectory);
            texture.Type = typeName;
            texture.FileName = str.C_Str();
            textures.push_back(texture);
            m_TexturesLoaded.push_back(texture);
        }
    }

    return textures;
}

unsigned int Model::TextureFromFile(const std::string &fileName, const std::string &filePath) {
    stbi_set_flip_vertically_on_load(1);

    int width, height, bpp;
    unsigned char *buffer = stbi_load((filePath + '/' + fileName).c_str(), &width, &height, &bpp, 4);
    assert(buffer != nullptr);

    unsigned int id = 0;
    GLCall(glGenTextures(1, &id));
    GLCall(glBindTexture(GL_TEXTURE_2D, id));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (buffer) {
        stbi_image_free(buffer);
        buffer = nullptr;
    } else {
        std::cout << "[WARNING]: Texture \'" << fileName << "\' hasn't been loaded!" << std::endl;
    }

    return id;
}