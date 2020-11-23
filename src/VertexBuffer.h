#pragma once

class VertexBuffer {
public:
    VertexBuffer();
    VertexBuffer(float *data, unsigned int size);
    ~VertexBuffer();

    void AttachData(float *data, unsigned int size);

    void Bind() const;
    void Unbind() const;

private:
    unsigned int m_RendererID;
};