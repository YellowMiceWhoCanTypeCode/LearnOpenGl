#include "Renderer.h"

Renderer::Renderer()
{
}

void Renderer::Render()
{
    shader_.use();
    vertex_array_.Bind();
    vertex_buffer_.Bind();
    index_buffer_.Bind();

    vertex_array_.SetVertexAttriPointer();
    glDrawElements(GL_TRIANGLES, index_buffer_.GetCount(), GL_UNSIGNED_INT, 0);
}
