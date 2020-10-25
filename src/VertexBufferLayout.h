#pragma once

#include "Renderer.h"

#include <vector>
#include <iostream>

struct VertexAttribute {
    unsigned int count;
    unsigned int type;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT: return 4;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout {
public:
    VertexBufferLayout() = default;
    ~VertexBufferLayout() = default;

    const std::vector<VertexAttribute> &GetElements() const { return m_Elements; }
    unsigned int GetStride() const { return m_Stride; }

    template<typename T>
    void Push(unsigned int count) {
        ASSERT(false);
    }

private:
    std::vector<VertexAttribute> m_Elements;
    unsigned int m_Stride;
};

template<>
inline void VertexBufferLayout::Push<float>(unsigned int count) {
    m_Elements.push_back({ count, GL_FLOAT, GL_FALSE });
    m_Stride += count * VertexAttribute::GetSizeOfType(GL_FLOAT);
}