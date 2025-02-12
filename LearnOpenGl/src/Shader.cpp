#include <fstream>
#include <sstream>
#include "glm.hpp"
#include <glad/glad.h>
#include "../include/Renderer/Shader.h"

#include <gtc/type_ptr.inl>

#include "spdlog/spdlog.h"


Shader::Shader(): ID(0)
{
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    spdlog::info("Shader:{} begin create!", vertexPath);
    //get vertex/fragment codes from file
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    //make sure ifstream can throw exception
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
        spdlog::error("Shader:{} read file coding fail!", vertexPath);
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    //compile shader
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    //vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    //print compile error(if have)
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        spdlog::error("Shader:{} vertex shader compile fail! Reason:{}", vertexPath, infoLog);
    };

    //fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    //print compile error(if have)
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        spdlog::error("Shader:{} fragment shader compile fail! Reason:{}", vertexPath, infoLog);
    };

    //shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    //print link error(if have)
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        spdlog::error("Shader:{} shader link fail! Reason:{}", vertexPath, infoLog);
    }

    //delete shader, because it has link to program ,we don`t need it
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    spdlog::info("Shader:{} create end!", vertexPath);
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
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
        spdlog::warn("Get Bool: {} Location Fail", name);
    }
    glUniform1i(location, (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    const GLint location = glGetUniformLocation(ID, name.c_str());
    if (location == -1)
    {
        spdlog::warn("Get Int: {} Location Fail", name);
    }
    glUniform1i(location, value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    const GLint location = glGetUniformLocation(ID, name.c_str());
    if (location == -1)
    {
        spdlog::warn("Get Float: {} Location Fail", name);
    }
    glUniform1f(location, value);
}

void Shader::setMat4(const std::string& name, gl_mat4 value) const
{
    const GLint location = glGetUniformLocation(ID, name.c_str());
    if (location == -1)
    {
        spdlog::warn("Get Mat4: {} Location Fail", name);
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, gl_vec3 value) const
{
    const GLint location = glGetUniformLocation(ID, name.c_str());
    if (location == -1)
    {
        spdlog::warn("Get Vec3: {} Location Fail", name);
    }
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
    setVec3(name, {x, y, z});
}
