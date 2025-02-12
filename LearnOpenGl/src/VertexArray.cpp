#include "../include/Renderer/VertexArray.h"

#include <glad/glad.h>


VertexArray::VertexArray(unsigned int attri_num, AttriType attri_type)
    : attri_num_(attri_num), attri_type_(attri_type)
{
    glGenVertexArrays(1, &vao_id_);
    glBindVertexArray(vao_id_);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &vao_id_);
}

void VertexArray::Bind()
{
    glBindVertexArray(vao_id_);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}

unsigned int VertexArray::GetID()
{
    return vao_id_;
}

void VertexArray::SetVertexAttriPointer()
{
    unsigned int count = 3 * attri_num_;
    if (attri_type_ & AttriType::Texcoord)
    {
        count -= 1;
    }

    unsigned int i = 0;
    unsigned int lay_out_index = 0;
    unsigned int runtime_offset = 0;
    for (; i < attri_num_; ++i)
    {
        int attri_count = 3;
        if (attri_type_ & (BIT(i)))
        {
            if ((attri_type_ & (BIT(i))) == AttriType::Texcoord)
                attri_count = 2;
            glVertexAttribPointer(lay_out_index, attri_count, GL_FLOAT, GL_FALSE, count * sizeof(float), (void*)(runtime_offset));
            glEnableVertexAttribArray(lay_out_index);
            ++lay_out_index;
            runtime_offset += attri_count;
        }
    }
}
