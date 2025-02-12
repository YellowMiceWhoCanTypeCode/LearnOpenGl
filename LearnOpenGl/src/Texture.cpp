#include "../include/Texture.h"

#include <iostream>
#include <stb_image.h>
#include <glad/glad.h>

Texture::Texture(const std::string& filePath)
    : file_path_(filePath)
{
    glGenTextures(1, &texture_ID_);
    int width, height, nrChannel;
    auto* data = stbi_load(filePath.c_str(), &width, &height, &nrChannel, 0);

    if (data)
    {
        GLenum format;
        if (nrChannel == 1)
            format = GL_RED;
        else if (nrChannel == 3)
            format = GL_RGB;
        else if (nrChannel == 4)
            format = GL_RGBA;
        glBindTexture(GL_TEXTURE_2D, texture_ID_);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << filePath << std::endl;
        stbi_image_free(data);
    }
}

void Texture::Bind(unsigned slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture_ID_);
}
