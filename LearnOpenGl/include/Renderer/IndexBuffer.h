#pragma once

class IndexBuffer
{
private:
    unsigned int ibo_id_;
    unsigned int m_Count;

public:
    IndexBuffer()
        : ibo_id_(0), m_Count(0)
    {
    }

    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    unsigned int GetID();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_Count; }
};
