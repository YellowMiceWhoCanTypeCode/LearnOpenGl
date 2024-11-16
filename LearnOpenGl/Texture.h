#pragma once
#include <iostream>
#include <stb_image.h>
#include <glad/glad.h>
#include <string>

class Texture
{
public:
    Texture(const std::string& path, GLenum target)
    {
        path_ = path;
        texture_target_ = target;
        glGenTextures(1, &ID);
        glBindTexture(target, ID);

        SetTexWrapParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
        SetTexWrapParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);

        SetTexFilterParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        SetTexFilterParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(path.c_str(), &width_, &height_, &nrChannels_, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_INT, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture in path:" << path << std::endl;
        }
        stbi_image_free(data);
    }

    void SetTexWrapParameteri(GLenum pname, const GLint param)
    {
        glTexParameteri(texture_target_, pname, param);
    }

    void SetTexFilterParameteri(GLenum pname, const GLint param)
    {
        glTexParameteri(texture_target_, pname, param);
    }

    unsigned id() const
    {
        return ID;
    }

    int width() const
    {
        return width_;
    }

    int height() const
    {
        return height_;
    }

    int nr_channels() const
    {
        return nrChannels_;
    }

    GLenum texture_target() const
    {
        return texture_target_;
    }

    std::string path() const
    {
        return path_;
    }

protected:
    unsigned int ID;
    int width_;
    int height_;
    int nrChannels_;
    GLenum texture_target_;
    std::string path_;
};
