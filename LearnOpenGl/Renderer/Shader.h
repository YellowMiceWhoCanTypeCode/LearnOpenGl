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
    // 程序ID
    unsigned int ID;

    Shader()
        : ID(0)
    {
    }

    // 构造器读取并构建着色器
    Shader(const char* vertexPath, const char* fragmentPath);
    Shader(const std::string& vertexPath, const std::string fragmentPath);
    // 使用/激活程序
    void use() const;
    // uniform工具函数
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, glm::mat4 value) const;
    void setVec3(const std::string& name, glm::vec3 value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
};

#endif
