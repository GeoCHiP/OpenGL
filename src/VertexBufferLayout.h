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
    VertexBufferLayout() : m_Stride(0) {};
    ~VertexBufferLayout() {};

    const std::vector<VertexAttribute> &GetAttributes() const { return m_Attributes; }
    unsigned int GetStride() const { return m_Stride; }

    template<typename T>
    void Push(unsigned int count) {
        ASSERT(false);
    }

private:
    std::vector<VertexAttribute> m_Attributes;
    unsigned int m_Stride;
};

template<>
inline void VertexBufferLayout::Push<float>(unsigned int count) {
    m_Attributes.push_back({ count, GL_FLOAT, GL_FALSE });
    m_Stride += count * VertexAttribute::GetSizeOfType(GL_FLOAT);
}