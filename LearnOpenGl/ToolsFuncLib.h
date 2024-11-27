#pragma once

#include <glad/glad.h>

#include <string>

namespace ToolsFuncLib
{
    GLuint loadTexture(const std::string& path)
    {
        // Generate texture ID and load texture data 
        GLuint textureID;
        glGenTextures(1, &textureID);
        int width, height, nrChannel;
        unsigned char* image = stbi_load(path.c_str(), &width, &height, &nrChannel, 0);
        // Assign texture to ID
        GLenum format = GL_RGB;
        if (nrChannel == 4)
        {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(image);
        return textureID;
    }
}
