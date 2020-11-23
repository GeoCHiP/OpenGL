#include "Renderer.h"

#include <iostream>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char *function, const char *file, int line) {
    bool fail = false;
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function << ' ' << file << ':' << line << std::endl;
        fail = true;
    }

    if (fail)
        return false;
    else
        return true;
}

Renderer::Renderer() {}
Renderer::~Renderer() {}

void Renderer::Clear() const {
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::DrawElements(const VertexArray &vao, const ElementBuffer &ebo, const Shader &shader) const {
    vao.Bind();
    ebo.Bind();
    shader.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawArrays(const VertexArray &vao, const Shader &shader, int first, unsigned int count) const {
    vao.Bind();
    shader.Bind();
    GLCall(glDrawArrays(GL_TRIANGLES, first, count));
}