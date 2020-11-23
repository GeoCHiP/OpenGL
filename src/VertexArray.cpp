#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer &vbo, const VertexBufferLayout &layout) {
    Bind();
    vbo.Bind();

    const auto &attributes = layout.GetAttributes();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < attributes.size(); ++i) {
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, attributes[i].count, attributes[i].type, attributes[i].normalized,
               layout.GetStride(), reinterpret_cast<const void *>(offset)));
        
        offset += attributes[i].count * VertexAttribute::GetSizeOfType(attributes[i].type);
    }
}

void VertexArray::Bind() const {
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const {
    GLCall(glBindVertexArray(0));
}