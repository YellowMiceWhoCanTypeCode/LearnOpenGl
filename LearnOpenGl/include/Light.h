#pragma once
#include <vec3.hpp>
#include <gtc/type_ptr.inl>

#include "Object.h"
#include "imgui/imgui.h"

enum class Light_Type
{
    Dir_Light = 0,
    Point_Light = 1,
    Spot_Light = 2
};

class Light : public Object
{
public:
    Light()
        : position_({0.0f, 1.0f, 0.0f}),
          direction_({0.0f, -1.0f, 0.0f}),
          ambient_({0.1f, 0.1f, 0.1f}),
          diffuse_({0.3f, 0.3f, 0.3f}),
          specular_({0.3f, 0.3f, 0.3f})
    {
    }

    Light(const LearnOpengl::Transform& transform);

    Light(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

    virtual ~Light() override;

    virtual void ImGui_ItemBind();

    virtual gl_mat4 GetLightSpaceMatrix(float far_plane) = 0;

    void AfterSpawn() override;

public:
    glm::vec3 position_;
    glm::vec3 direction_;
    glm::vec3 ambient_;
    glm::vec3 diffuse_;
    glm::vec3 specular_;

    Light_Type light_type_;
};

// parallel lighting
class DirLight : public Light
{
public:
    DirLight();

    DirLight(const LearnOpengl::Transform& transform);

    DirLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

    virtual ~DirLight() override;

    void ImGui_ItemBind() override;

    gl_mat4 GetLightSpaceMatrix(float far_plane) override;

public:
};

/* 点光源参考数值
距离	    常数项	一次项	二次项
7	    1.0	    0.7	    1.8
13	    1.0	    0.35	0.44
20	    1.0	    0.22	0.20
32	    1.0	    0.14	0.07
50	    1.0	    0.09	0.032
65	    1.0	    0.07	0.017
100	    1.0	    0.045	0.0075
160	    1.0	    0.027	0.0028
200	    1.0	    0.022	0.0019
325	    1.0	    0.014	0.0007
600	    1.0	    0.007	0.0002
3250    1.0	    0.0014	0.000007
*/

// point light
class PointLight : public Light
{
public:
    PointLight();

    PointLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);

    virtual ~PointLight();

    void ImGui_ItemBind() override;

    gl_mat4 GetLightSpaceMatrix(float far_plane) override;

public:
    float constant_;
    float linear_;
    float quadratic_;
};

/* 聚光灯参考数值
θ       θ （角度）	ϕ （内光切）	ϕ （角度）	γ （外光切）	γ （角度）	ϵ                       I
0.87	30	        0.91	    25	        0.82	    35	        0.91 - 0.82 = 0.09	    0.87 - 0.82 / 0.09 = 0.56
0.9	    26	        0.91	    25	        0.82	    35	        0.91 - 0.82 = 0.09	    0.9 - 0.82 / 0.09 = 0.89
0.97	14	        0.91	    25	        0.82	    35	        0.91 - 0.82 = 0.09	    0.97 - 0.82 / 0.09 = 1.67
0.83	34	        0.91	    25	        0.82	    35	        0.91 - 0.82 = 0.09	    0.83 - 0.82 / 0.09 = 0.11
0.64	50	        0.91	    25	        0.82	    35	        0.91 - 0.82 = 0.09	    0.64 - 0.82 / 0.09 = -2.0
0.966	15	        0.9978	    12.5	    0.953	    17.5	    0.9978 - 0.953 = 0.0448	0.966 - 0.953 / 0.0448 = 0.29
*/

// spot light
class SpotLight : public Light
{
public:
    SpotLight();

    SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float cutOff, float outerCutOff, float constant, float linear,
              float quadratic);

    virtual ~SpotLight();

    void ImGui_ItemBind() override;

public:
    float cutOff_;
    float outerCutOff_;
    float constant_;
    float linear_;
    float quadratic_;
};
