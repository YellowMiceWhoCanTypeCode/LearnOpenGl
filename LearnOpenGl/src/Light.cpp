#include "../Core.h"
#include "../include/Light.h"

#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>

#include "../include/Renderer/RenderingController.h"

Light::Light(
    glm::vec3 position,
    glm::vec3 direction,
    glm::vec3 ambient,
    glm::vec3 diffuse,
    glm::vec3 specular)
    : position_(position), direction_(direction), ambient_(ambient), diffuse_(diffuse), specular_(specular)
{
}

Light::~Light()
{
}

void Light::ImGui_ItemBind()
{
    ImGui::SliderFloat3(u8"位置", glm::value_ptr(position_), -10.0f, 10.0f);
    ImGui::SliderFloat3(u8"方向", glm::value_ptr(direction_), -1.0f, 1.0f);
    ImGui::SliderFloat3(u8"环境光颜色", glm::value_ptr(ambient_), -1.0f, 1.0f);
    ImGui::SliderFloat3(u8"漫反射颜色", glm::value_ptr(diffuse_), -1.0f, 1.0f);
    ImGui::SliderFloat3(u8"高光颜色", glm::value_ptr(specular_), -1.0f, 1.0f);
}

void Light::AfterSpawn()
{
    auto* rendering_controller = RenderingController::Get();
    rendering_controller->AddLight(this);
}

DirLight::DirLight()
{
    light_type_ = Light_Type::Dir_Light;
}

DirLight::DirLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular): Light(position, direction, ambient, diffuse, specular)
{
}

DirLight::~DirLight()
{
}

void DirLight::ImGui_ItemBind()
{
    Light::ImGui_ItemBind();
}

gl_mat4 DirLight::GetLightSpaceMatrix(float far_plane)
{
    constexpr float near_plane = 0.1f;
    const gl_mat4 light_view = glm::lookAt(position_, gl_vec3(0.0f), gl_vec3(0.0f, 1.0f, 0.0f));
    const gl_mat4 light_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    return light_projection * light_view;
}

PointLight::PointLight(): constant_(1.0f),
                          linear_(0.09f),
                          quadratic_(0.032f)
{
    light_type_ = Light_Type::Point_Light;
}

PointLight::PointLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic):
    Light(position, direction, ambient, diffuse, specular),
    constant_(constant),
    linear_(linear),
    quadratic_(quadratic)
{
}

PointLight::~PointLight()
{
}

void PointLight::ImGui_ItemBind()
{
    Light::ImGui_ItemBind();
    ImGui::SliderFloat(u8"衰减常系数", &constant_, 0.0f, 2.0f);
    ImGui::SliderFloat(u8"衰减一次项系数", &linear_, 0.0f, 1.0f);
    ImGui::SliderFloat(u8"衰减二次项系数", &quadratic_, 0.0f, 1.0f);
}

gl_mat4 PointLight::GetLightSpaceMatrix(float far_plane)
{
    return glm::mat4(1.0);
}

SpotLight::SpotLight(): cutOff_(12.5f),
                        outerCutOff_(17.5f),
                        constant_(1.0f),
                        linear_(0.09f),
                        quadratic_(0.032f)
{
    light_type_ = Light_Type::Spot_Light;
}

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float cutOff, float outerCutOff, float constant,
                     float linear, float quadratic): Light(position, direction, ambient, diffuse, specular),
                                                     cutOff_(cutOff),
                                                     outerCutOff_(outerCutOff),
                                                     constant_(constant),
                                                     linear_(linear),
                                                     quadratic_(quadratic)
{
}

SpotLight::~SpotLight()
{
}

void SpotLight::ImGui_ItemBind()
{
    Light::ImGui_ItemBind();
    ImGui::SliderFloat(u8"内光切", &cutOff_, 1.0f, 179.0f);
    ImGui::SliderFloat(u8"外光切", &outerCutOff_, 1.0f, 179.0f);
    ImGui::SliderFloat(u8"衰减常系数", &constant_, 0.0f, 2.0f);
    ImGui::SliderFloat(u8"衰减一次项系数", &linear_, 0.0f, 1.0f);
    ImGui::SliderFloat(u8"衰减二次项系数", &quadratic_, 0.0f, 1.0f);
}
