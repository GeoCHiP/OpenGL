#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer &vbo, const VertexBufferLayout &layout);

    void Bind() const;
    void Unbind() const;

private:
    unsigned int m_RendererID;
};