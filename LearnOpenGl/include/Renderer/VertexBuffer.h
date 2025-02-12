#pragma once

class VertexBuffer
{
private:
    unsigned int vbo_id_;

public:
    VertexBuffer()
        : vbo_id_(0)
    {
    }

    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind();
    void Unbind();

    unsigned int GetID();
};
