#include "../include/InputDispatcher.h"

#include "../include/Actor.h"
#include "../include/GameInstance.h"
#include "../vendor/imgui/imgui_internal.h"
#include "../include/Camera.h"
#include "../include/World.h"

InputDispatcher* InputDispatcher::input_dispatcher_ = nullptr;

InputDispatcher* InputDispatcher::Get()
{
    static auto* dispatcher = new InputDispatcher;
    input_dispatcher_ = dispatcher;
    return dispatcher;
}

void InputDispatcher::HandleInputEvents(GLFWwindow* window)
{
    const auto* game_instance = GameInstance::Get();
    auto* camera = game_instance->world_->player_->GetCameraComponent();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, game_instance->delta_time_);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, game_instance->delta_time_);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, game_instance->delta_time_);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, game_instance->delta_time_);
}

void InputDispatcher::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    auto* game_instance = GameInstance::Get();
    game_instance->window_width_ = width;
    game_instance->window_height_ = height;
    glViewport(0, 0, width, height);
}

void InputDispatcher::CursorPosCallback(GLFWwindow* window, double x, double y)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2((float)x, (float)y);
    if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS) || io.WantCaptureMouse == true)
    {
        input_dispatcher_->last_cursor_x_ = x;
        input_dispatcher_->last_cursor_y_ = y;
        return;
    }

    input_dispatcher_->curr_cursor_x_ = x;
    input_dispatcher_->curr_cursor_y_ = y;
    if (input_dispatcher_->cursor_first_move_)
    {
        input_dispatcher_->last_cursor_x_ = x;
        input_dispatcher_->last_cursor_y_ = y;
        input_dispatcher_->cursor_first_move_ = false;
    }

    double xoffset = input_dispatcher_->curr_cursor_x_ - input_dispatcher_->last_cursor_x_;
    double yoffset = input_dispatcher_->curr_cursor_y_ - input_dispatcher_->last_cursor_y_;

    input_dispatcher_->last_cursor_x_ = x;
    input_dispatcher_->last_cursor_y_ = y;

    GameInstance::Get()->world_->player_->GetCameraComponent()->ProcessMouseMovement(xoffset, yoffset);
}

void InputDispatcher::ScrollCallback(GLFWwindow* window, double x_offset, double y_offset)
{
    GameInstance::Get()->world_->player_->GetCameraComponent()->ProcessMouseScroll(static_cast<float>(y_offset));
}
