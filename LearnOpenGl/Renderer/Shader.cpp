#include "Shader.h"
#include "../Core.h"

#include "glm.hpp"
#include <gtc/type_ptr.inl>

#include <fstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    //【1】从文件中获取顶点/片段着色器
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    //保证ifstream对象可以抛出异常
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    //【2】编译着色器
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // 顶点着色器
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // 打印编译错误（如果有的话）
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    //片段着色器
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // 打印编译错误（如果有的话）
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // 着色器程序
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // 打印连接错误（如果有的话）
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::Shader(const std::string& vertexPath, const std::string fragmentPath)
    : Shader(vertexPath.c_str(), fragmentPath.c_str())
{
}

void Shader::use() const
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
    const GLint location = glGetUniformLocation(ID, name.c_str());
    if (location == -1)
    {
        Debug_OutPut("Error:Get Bool Location False");
    }
    glUniform1i(location, (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    const GLint location = glGetUniformLocation(ID, name.c_str());
    if (location == -1)
    {
        Debug_OutPut("Error:Get Int Location False");
    }
    glUniform1i(location, value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    const GLint location = glGetUniformLocation(ID, name.c_str());
    if (location == -1)
    {
        Debug_OutPut("Error:Get Float Location False");
    }
    glUniform1f(location, value);
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const
{
    const GLint location = glGetUniformLocation(ID, name.c_str());
    if (location == -1)
    {
        Debug_OutPut("Error:Get Mat4 Location False");
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, glm::vec3 value) const
{
    const GLint location = glGetUniformLocation(ID, name.c_str());
    if (location == -1)
    {
        Debug_OutPut("Error:Get Vec3 Location False");
    }
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
    setVec3(name, {x, y, z});
}
