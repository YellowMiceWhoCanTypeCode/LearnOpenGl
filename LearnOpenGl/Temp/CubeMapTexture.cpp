#include "CubeMapTexture.h"

#include "../MyTexture.h"

CubeMapTexture::CubeMapTexture(const std::string paths[6])
{
    glGenTextures(1, &textureID_);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID_);
    unsigned char* data = nullptr;
    int width, height, nrChannel;
    for (int i = 0; i < 6; ++i)
    {
        data = stbi_load(paths[i].c_str(), &width, &height, &nrChannel, 0);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        datas_[i] = data;
    }
}

void CubeMapTexture::Bind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID_);
}

void CubeMapTexture::Unbind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
