#pragma once

#include <GL/glew.h>
#include <csignal>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if(!(x)) raise(SIGABRT)
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char *function, const char *file, int line);

class Renderer {
public:
    Renderer();
    ~Renderer();

    void Clear() const;
    void DrawElements(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
    void DrawArrays(const VertexArray &va, const Shader &shader, int first, unsigned int count) const;
};