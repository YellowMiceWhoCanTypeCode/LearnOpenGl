#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

class Renderer
{
public:
    Renderer();

    void Render();

private:
    VertexArray vertex_array_;
    VertexBuffer vertex_buffer_;
    IndexBuffer index_buffer_;
    Shader shader_;
};
