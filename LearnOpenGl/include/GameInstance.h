#pragma once

#include <GLFW/glfw3.h>


class World;

// 游戏示例对象，单例，全局唯一
class GameInstance
{
public:
    static GameInstance* Get();

    // 每次游戏循环时，记录与上一次循环的帧数差
    void UpdateFrame();

private:
    GameInstance();

    //窗口初始化
    void WindowInit();

    //Imgui初始化
    void ImguiInit();

    //输处理器初始化
    void InputDispatcherInit() const;

public:
    // 窗口对象引用
    GLFWwindow* window_ = nullptr;
    // 世界对象引用
    World* world_ = nullptr;
    // 窗口大小记录
    unsigned int window_width_ = 800;
    unsigned int window_height_ = 600;
    // 时间记录
    float delta_time_ = 0.0f;
    float last_frame_ = 0.0f;

private:
};
