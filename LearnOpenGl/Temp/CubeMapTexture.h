#pragma once

#include <string>

class CubeMapTexture
{
public:
    CubeMapTexture(const std::string paths[6]);

    void Bind();
    void Unbind();

private:
    unsigned int textureID_;

    unsigned char* datas_[6];
};
