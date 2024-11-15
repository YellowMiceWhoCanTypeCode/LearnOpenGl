#pragma once

#ifndef SHADER_H
#define SHADRE_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <fwd.hpp>
#include <sstream>
#include <iostream>

class Shader
{
public:
    // ����ID
    unsigned int ID;

    // ��������ȡ��������ɫ��
    Shader(const char* vertexPath, const char* fragmentPath);
    // ʹ��/�������
    void use();
    // uniform���ߺ���
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMatrix(const std::string& name, glm::mat4 value) const;
};

#endif
