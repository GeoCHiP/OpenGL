#pragma once

class VertexBuffer {
public:
    VertexBuffer(float *data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

private:
    unsigned int m_RendererID;
};