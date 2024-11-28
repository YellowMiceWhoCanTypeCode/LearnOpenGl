#pragma once
#include <vec3.hpp>
#include <gtc/type_ptr.inl>

#include "vendor/imgui/imgui.h"

class Light
{
public:
    Light()
        : position_({0.0f, 0.0f, 0.0f}),
          direction_({0.0f, -1.0f, 0.0f}),
          ambient_({0.1f, 0.1f, 0.1f}),
          diffuse_({0.3f, 0.3f, 0.3f}),
          specular_({0.3f, 0.3f, 0.3f})
    {
    }

    Light(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
        : position_(position),
          direction_(direction),
          ambient_(ambient),
          diffuse_(diffuse),
          specular_(specular)
    {
    }

    virtual ~Light()
    {
    }

    virtual void ImGui_ItemBind()
    {
        ImGui::SliderFloat3(u8"位置", glm::value_ptr(position_), -10.0f, 10.0f);
        ImGui::SliderFloat3(u8"方向", glm::value_ptr(direction_), -1.0f, 1.0f);
        ImGui::SliderFloat3(u8"环境光颜色", glm::value_ptr(ambient_), -1.0f, 1.0f);
        ImGui::SliderFloat3(u8"漫反射颜色", glm::value_ptr(diffuse_), -1.0f, 1.0f);
        ImGui::SliderFloat3(u8"高光颜色", glm::value_ptr(specular_), -1.0f, 1.0f);
    }

public:
    glm::vec3 position_;
    glm::vec3 direction_;
    glm::vec3 ambient_;
    glm::vec3 diffuse_;
    glm::vec3 specular_;
};

// 
class DirLight : public Light
{
public:
    DirLight() : Light()
    {
    }

    DirLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
        : Light(position, direction, ambient, diffuse, specular)
    {
    }

    virtual ~DirLight()
    {
    }

    void ImGui_ItemBind() override
    {
        Light::ImGui_ItemBind();
    }

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

//
class PointLight : public Light
{
public:
    PointLight()
        : constant_(1.0f),
          linear_(0.09f),
          quadratic_(0.032f)
    {
    }

    PointLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
        : Light(position, direction, ambient, diffuse, specular),
          constant_(constant),
          linear_(linear),
          quadratic_(quadratic)
    {
    }

    virtual ~PointLight()
    {
    }

    void ImGui_ItemBind() override
    {
        Light::ImGui_ItemBind();
        ImGui::SliderFloat(u8"衰减常系数", &constant_, 0.0f, 2.0f);
        ImGui::SliderFloat(u8"衰减一次项系数", &linear_, 0.0f, 1.0f);
        ImGui::SliderFloat(u8"衰减二次项系数", &quadratic_, 0.0f, 1.0f);
    }

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

class SpotLight : public Light
{
public:
    SpotLight()
        : cutOff_(12.5f),
          outerCutOff_(17.5f),
          constant_(1.0f),
          linear_(0.09f),
          quadratic_(0.032f)
    {
    }

    SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float cutOff, float outerCutOff, float constant, float linear,
              float quadratic)
        : Light(position, direction, ambient, diffuse, specular),
          cutOff_(cutOff),
          outerCutOff_(outerCutOff),
          constant_(constant),
          linear_(linear),
          quadratic_(quadratic)
    {
    }

    virtual ~SpotLight()
    {
    }

    void ImGui_ItemBind() override
    {
        Light::ImGui_ItemBind();
        ImGui::SliderFloat(u8"内光切", &cutOff_, 1.0f, 179.0f);
        ImGui::SliderFloat(u8"外光切", &outerCutOff_, 1.0f, 179.0f);
        ImGui::SliderFloat(u8"衰减常系数", &constant_, 0.0f, 2.0f);
        ImGui::SliderFloat(u8"衰减一次项系数", &linear_, 0.0f, 1.0f);
        ImGui::SliderFloat(u8"衰减二次项系数", &quadratic_, 0.0f, 1.0f);
    }

public:
    float cutOff_;
    float outerCutOff_;
    float constant_;
    float linear_;
    float quadratic_;
};
