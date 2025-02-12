#pragma once
#define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h>

// 输出处理中心
class InputDispatcher
{
public:
    static InputDispatcher* Get();

    static void HandleInputEvents(GLFWwindow* window);

    static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

    static void CursorPosCallback(GLFWwindow* window, double x, double y);

    static void ScrollCallback(GLFWwindow* window, double x_offset, double y_offset);

public:
    static InputDispatcher* input_dispatcher_;

private:
    InputDispatcher() = default;

    double curr_cursor_x_ = 0;
    double curr_cursor_y_ = 0;
    double last_cursor_x_ = 0;
    double last_cursor_y_ = 0;
    bool cursor_first_move_ = true;
};
