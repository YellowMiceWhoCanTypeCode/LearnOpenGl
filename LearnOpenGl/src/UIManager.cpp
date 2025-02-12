#include "../Core.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

#include "../include/UI/UIManager.h"
#include "../include/GameInstance.h"
#include "../include/UI/GL_Window.h"


UIManager* UIManager::Get()
{
    static UIManager* ui_manager = new UIManager;
    return ui_manager;
}

void UIManager::Update(float delta)
{
    //judge window state is OK
    if (glfwGetWindowAttrib(GameInstance::Get()->window_, GLFW_ICONIFIED) != 0)
    {
        ImGui_ImplGlfw_Sleep(10);
        return;
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //TODO:remember to delete , temp added
    ImGui::ShowDemoWindow(&show_demo_window_);

    //windows by windows rendering
    for (auto* gl_window : gl_windows_)
    {
        gl_window->Render();
    }

    //开始渲染UI
    ImGui::Render();

    int display_w, display_h;
    glfwGetFramebufferSize(GameInstance::Get()->window_, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

GL_Window* UIManager::CreateWindow(const std::string& window_name)
{
    const auto iter = gl_map_windows_.find(window_name);
    if (iter != gl_map_windows_.end())
    {
        Debug_OutPut(window_name + " window already exist, create fail!");
        return iter->second;
    }
    auto* new_window = new GL_Window(window_name);
    gl_windows_.push_back(new_window);
    gl_map_windows_.insert(std::pair{window_name, new_window});
    return new_window;
}

UIManager::UIManager()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    //set imgui style
    ImGui::StyleColorsDark();

    //set platform/renderer backends
    ImGui_ImplGlfw_InitForOpenGL(GameInstance::Get()->window_, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    //add chinese fonts
    ImFont* font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\msyh.ttc", 18.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());
    if (!font)
    {
        std::cerr << "Failed to load Chinese font!" << std::endl;
    }
}
