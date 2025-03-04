﻿#include "../include/Mesh.h"

#include <glad/glad.h>
#include <string>
#include <vector>
#include <ext/matrix_transform.hpp>

#include "../include/Actor.h"
#include "../include/Camera.h"
#include "../include/GameInstance.h"
#include "../include/Material.h"
#include "../include/Object.h"
#include "../include/Texture.h"
#include "../include/World.h"
#include "../include/Renderer/Shader.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, Material* material)
{
    this->vertices = vertices;
    this->indices = indices;
    this->material_ = material;

    // now that we have all the required data, set the vertex buffers and its attribute pointers.
    setupMesh();
}

void Mesh::Draw(Shader* shader, const Object* owner)
{
    material_->Apply(shader);
    /*// bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i]->texture_type_;
        if (name == "texture_diffuse")
        {
            name = "diffuse";
            number = std::to_string(diffuseNr++);
        }
        else if (name == "texture_specular")
        {
            name = "specular";
            number = std::to_string(specularNr++); // transfer unsigned int to string
        }
        else if (name == "texture_normal")
        {
            name = "normal";
            number = std::to_string(normalNr++); // transfer unsigned int to string
        }
        else if (name == "texture_height")
        {
            name = "height";
            number = std::to_string(heightNr++); // transfer unsigned int to string
        }

        shader->setInt(name, i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i]->texture_ID_);
    }*/

    auto* game_instance = GameInstance::Get();
    auto* camera = game_instance->world_->player_->GetCameraComponent();

    gl_mat4 model(1.0);
    model = glm::translate(model, owner->transform_.position);
    model = glm::rotate(model, glm::radians(owner->transform_.rotate.x), gl_vec3{1.0f, 0.0f, 0.0f});
    model = glm::rotate(model, glm::radians(owner->transform_.rotate.y), gl_vec3{0.0f, 1.0f, 0.0f});
    model = glm::rotate(model, glm::radians(owner->transform_.rotate.z), gl_vec3{0.0f, 0.0f, 1.0f});
    model = glm::scale(model, owner->transform_.scale);

    /*gl_mat4 view(1.0);
    view = camera->GetViewMatrix();

    gl_mat4 projection(1.0);
    projection = glm::perspective(
        glm::radians(camera->Zoom),
        (float)game_instance->window_width_ / (float)game_instance->window_height_,
        camera->zNear,
        camera->zFar
    );
    material_->shader_->setMat4("view", view);
    material_->shader_->setMat4("projection", projection);*/

    shader->setMat4("model", model);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    // ids
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));
    // weights
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
    glBindVertexArray(0);
}
