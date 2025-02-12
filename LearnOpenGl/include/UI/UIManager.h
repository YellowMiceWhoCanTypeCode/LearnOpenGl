#pragma once
#include <unordered_map>

#include "GL_Window.h"
#include "../../Core.h"
class UI_Component;
class GL_Window;

class UIManager
{
public:
    static UIManager* Get();

    void Update(float delta);

    GL_Window* CreateWindow(const std::string& window_name);

    template <typename T>
    void CreateComponent(const std::string& window_name)
    {
        static_assert(std::is_base_of_v<UI_Component, T>, "Error:creating UI_Component isn`t UI_Component`s Child");
        const auto iter = gl_map_windows_.find(window_name);
        if (iter == gl_map_windows_.end())
        {
            Debug_OutPut(window_name + " window not exist, create and add ui_component fail!");
            return;
        }
        auto* new_ui_component = new T;
        iter->second->AddComponent(new_ui_component);
    }

private:
    UIManager();

    std::unordered_map<std::string, GL_Window*> gl_map_windows_;
    std::vector<GL_Window*> gl_windows_;

    //TODO:remember to delete, temp added
    bool show_demo_window_ = true;
};
