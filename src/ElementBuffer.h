#pragma once

class ElementBuffer {
public:
    ElementBuffer(unsigned int *data, unsigned int count);
    ~ElementBuffer();

    void Bind() const;
    void Unbind() const;

    unsigned int GetCount() const;

private:
    unsigned int m_RendererID;
    unsigned int m_Count;
};