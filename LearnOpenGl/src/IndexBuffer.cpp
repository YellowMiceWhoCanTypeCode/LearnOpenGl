#include "../include/Renderer/IndexBuffer.h"

#include <glad/glad.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned count)
    : m_Count(count)
{
    glGenBuffers(1, &ibo_id_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &ibo_id_);
}

unsigned IndexBuffer::GetID()
{
    return ibo_id_;
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id_);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
