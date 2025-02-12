#include <iostream>
#include <glad/glad.h>

#include "../include/GameInstance.h"
#include "../include/InputDispatcher.h"
#include "../include/UI/UIManager.h"
#include "../include/World.h"
#include "../vendor/spdlog/spdlog.h"


GameInstance* GameInstance::Get()
{
    // 单例构造，保证GameInstance的唯一
    static auto* game_instance = new GameInstance();
    return game_instance;
}

void GameInstance::UpdateFrame()
{
    const auto current_frame = static_cast<float>(glfwGetTime());
    delta_time_ = current_frame - last_frame_;
    last_frame_ = current_frame;
}

GameInstance::GameInstance()
{
    spdlog::info("GameInstance construct begin!");
    //初始化window
    WindowInit();

    //不进行Imgui的初始化，在第一次渲染循环时进行Imgui的初始化，避免在GameInstance::Get中调用GameInstance::Get

    //输入处理器初始化
    InputDispatcherInit();

    //世界创建
    auto* world = new World();
    this->world_ = world;
    spdlog::info("GameInstance construct end!");
}

void GameInstance::WindowInit()
{
    spdlog::info("glfw init begin!");
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    GLFWwindow* window = glfwCreateWindow(window_width_, window_height_, "LearnOpenGL", NULL, NULL);
    if (window == nullptr)
    {
        spdlog::error("Failed to create GLFW window!");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); //enable vertical sync
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        spdlog::error("Failed to initialize GLAD!");
        return;
    }
    window_ = window;
    spdlog::info("glfw init end!");
}

void GameInstance::ImguiInit()
{
    //第一次获得UI管理器，触发UIManager的单例构造
    UIManager::Get();
}

void GameInstance::InputDispatcherInit() const
{
    spdlog::info("InputDispatcher Init begin!");
    InputDispatcher::Get();
    glfwSetFramebufferSizeCallback(window_, InputDispatcher::FrameBufferSizeCallback);
    glfwSetCursorPosCallback(window_, InputDispatcher::CursorPosCallback);
    glfwSetScrollCallback(window_, InputDispatcher::ScrollCallback);
    spdlog::info("InputDispatcher Init end!");
}
