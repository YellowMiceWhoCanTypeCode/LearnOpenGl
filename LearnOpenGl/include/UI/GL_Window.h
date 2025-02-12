#pragma once
#include <string>
#include <vector>

class UI_Component;

//window class,it has only basic property and UI_Component
class GL_Window
{
public:
    GL_Window();

    GL_Window(const std::string& window_name);

    ~GL_Window();

    void Render();

    void AddComponent(UI_Component* ui_component);

protected:
    std::string window_name_;

    std::vector<UI_Component*> ui_components_;
};
