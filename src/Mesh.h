#pragma once

#include "Shader.h"

#include "glm/glm.hpp"

#include <vector>
#include <string>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoord;
};

struct TextureInfo {
    unsigned int Id;
    std::string Type;
    std::string FilePath;
};

class Mesh {
public:
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    std::vector<TextureInfo> Textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
         std::vector<TextureInfo> textures);

    void Draw(Shader &shader);

private:
    void SetupMesh();

private:
    unsigned int m_VAO, m_VBO, m_EBO;
};