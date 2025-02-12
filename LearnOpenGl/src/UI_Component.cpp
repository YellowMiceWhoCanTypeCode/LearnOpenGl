#include "../include/UI/UI_Component.h"

#include "../include/Renderer/RenderingController.h"
#include "../vendor/imgui/imgui.h"

UI_Component::UI_Component()
{
}

RenderingSettingComponent::RenderingSettingComponent()
{
}

void RenderingSettingComponent::Render()
{
    auto* rendering_controller = RenderingController::Get();
    /*ImGui::InputFloat3("Shen_Li Position", );
    ImGui::InputFloat3("Gan_Yv Position", );
    ImGui::InputFloat3("Light Position", );
    ImGui::InputFloat3("Light Color", );*/
    ImGui::Checkbox("Enable SSAO", &rendering_controller->enable_ssao_);
    ImGui::Checkbox("Enable Anti-Aliasing", &rendering_controller->enable_anti_aliasing_);
}
