#include "Mesh.h"
#include "Renderer.h"

#include "GL/glew.h"

#include <string>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
         std::vector<TextureInfo> textures)
         : Vertices(vertices), Indices(indices), Textures(textures) {
    SetupMesh();
}

void Mesh::SetupMesh() {
    GLCall(glGenVertexArrays(1, &m_VAO));
    GLCall(glGenBuffers(1, &m_VBO));
    GLCall(glGenBuffers(1, &m_EBO));

    GLCall(glBindVertexArray(m_VAO));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
    GLCall(glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), Vertices.data(), GL_STATIC_DRAW));

    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), Indices.data(), GL_STATIC_DRAW));

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0));

    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Normal)));

    GLCall(glEnableVertexAttribArray(2));
    GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoord)));

    GLCall(glBindVertexArray(0));
}

void Mesh::Draw(Shader &shader) {
    unsigned int diffuseNum = 1;
    unsigned int specularNum = 1;
    shader.Bind();
    for (int i = 0; i < Textures.size(); ++i) {
        GLCall(glActiveTexture(GL_TEXTURE0 + i));
        std::string number;
        std::string type = Textures[i].Type;
        if (type == "texture_diffuse")
            number = std::to_string(diffuseNum++);
        else if (type == "texture_specular")
            number = std::to_string(specularNum++);
        shader.SetUniform1i(type + number, i);
        GLCall(glBindTexture(GL_TEXTURE_2D, Textures[i].Id));
    }

    GLCall(glBindVertexArray(m_VAO));
    GLCall(glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, nullptr));
    GLCall(glBindVertexArray(0));

    GLCall(glActiveTexture(GL_TEXTURE0));
}