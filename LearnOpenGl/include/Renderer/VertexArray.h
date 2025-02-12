#pragma once

#define BIT(x) (1 << (x))

enum AttriType
{
    Position = 0,
    Color = BIT(1),
    Texcoord = BIT(2),
    Diffuse = BIT(3),
    Specular = BIT(4)
};

class VertexArray
{
public:
    VertexArray()
        : vao_id_(0), attri_num_(0), attri_type_(AttriType::Position)
    {
    }

    VertexArray(unsigned int attri_num, AttriType attri_type);
    ~VertexArray();

    void Bind();
    void Unbind();

    unsigned int GetID();

    void SetVertexAttriPointer();

private:
    unsigned int vao_id_;
    unsigned int attri_num_;
    AttriType attri_type_;
};
