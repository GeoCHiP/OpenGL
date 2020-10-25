#pragma once

#include "Renderer.h"

class IndexBuffer {
public:
    IndexBuffer(unsigned int *data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

private:
    unsigned int m_RendererID;
    unsigned int m_Count;
};