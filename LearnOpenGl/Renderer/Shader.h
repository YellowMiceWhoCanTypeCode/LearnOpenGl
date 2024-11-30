#pragma once

#ifndef SHADER_H
#define SHADRE_H

#include <glad/glad.h>

#include <string>
#include <fwd.hpp>
#include <sstream>

class Shader
{
public:
    // ����ID
    unsigned int ID;

    Shader()
        : ID(0)
    {
    }

    // ��������ȡ��������ɫ��
    Shader(const char* vertexPath, const char* fragmentPath);
    Shader(const std::string& vertexPath, const std::string fragmentPath);
    // ʹ��/�������
    void use() const;
    // uniform���ߺ���
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, glm::mat4 value) const;
    void setVec3(const std::string& name, glm::vec3 value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
};

#endif
