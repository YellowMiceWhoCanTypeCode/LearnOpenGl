#include "../include/UI/GL_Window.h"

#include "../include/UI/UI_Component.h"
#include "../vendor/imgui/imgui_internal.h"

GL_Window::GL_Window()
    : window_name_("")
{
}

GL_Window::GL_Window(const std::string& window_name)
    : window_name_(window_name)
{
}

GL_Window::~GL_Window()
{
    for (const auto* ui_component : ui_components_)
    {
        delete ui_component;
    }
}

void GL_Window::Render()
{
    ImGui::Begin(window_name_.c_str());

    for (auto* ui_component : ui_components_)
    {
        ui_component->Render();
    }

    ImGui::End();
}

void GL_Window::AddComponent(UI_Component* ui_component)
{
    ui_components_.push_back(ui_component);
}
