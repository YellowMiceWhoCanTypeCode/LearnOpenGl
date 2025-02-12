#pragma once
#include "../../Core.h"
#include <string>


class Shader
{
public:
    unsigned int ID;

    Shader();
    Shader(const char* vertexPath, const char* fragmentPath);
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    void use() const;

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, gl_mat4 value) const;
    void setVec3(const std::string& name, gl_vec3 value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
};
