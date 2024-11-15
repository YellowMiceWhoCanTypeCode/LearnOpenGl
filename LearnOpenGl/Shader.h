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
    // 程序ID
    unsigned int ID;

    // 构造器读取并构建着色器
    Shader(const char* vertexPath, const char* fragmentPath);
    // 使用/激活程序
    void use();
    // uniform工具函数
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMatrix(const std::string& name, glm::mat4 value) const;
};

#endif
