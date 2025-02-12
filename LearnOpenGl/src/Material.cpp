#include "../Core.h"
#include <glad/glad.h>
#include <stb_image.h>
#include <assimp/material.h>

#include "../include/Material.h"
#include "../include/Texture.h"
#include "../include/Renderer/Shader.h"

inline unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = true)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    // stbi_set_flip_vertically_on_load(true);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format = GL_RGB;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Model.h::Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

Material::Material()
{
}

Material::~Material()
{
}

bool Material::Bind_Impl(Shader* shader, Texture* texture, const std::string& tex_name, int& slot) const
{
    if (texture == nullptr)
    {
        return false;
    }
    texture->Bind(GL_TEXTURE0 + slot);
    shader->setInt(tex_name, slot++);
    return true;
}

void Material::Gene_Impl(aiMaterial* material, Texture*& texture, aiTextureType texture_type, const std::string& directory) const
{
    aiString str;
    material->GetTexture(texture_type, 0, &str);
    if (str.length != 0)
    {
        texture = new Texture;
        texture->texture_ID_ = TextureFromFile(str.C_Str(), directory);
        texture->file_path_ = str.C_Str();
        texture->texture_type_ = "DIFFUSE";
    }
}

Cartoon_Material::Cartoon_Material()
{
}

void Cartoon_Material::Generate(aiMaterial* material, const std::string& directory)
{
    Gene_Impl(material, color_map_, aiTextureType_DIFFUSE, directory);
    //Gene_Impl(material, shadow_map_, aiTextureType_DIFFUSE, directory);
    //Gene_Impl(material, color_map_, aiTextureType_DIFFUSE, directory);
}

void Cartoon_Material::Apply(Shader* shader)
{
    shader->use();
    int slot = 0;

    Bind_Impl(shader, color_map_, "color_map", slot);
    Bind_Impl(shader, shadow_map_, "shadow_map", slot);
    Bind_Impl(shader, outline_map_, "outline_map", slot);
}
