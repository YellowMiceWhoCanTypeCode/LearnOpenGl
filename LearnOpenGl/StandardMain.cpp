#include "Core.h"
#include "include/GameInstance.h"
#include "include/Model.h"
#include "include/World.h"
#include "include/Actor.h"
#include "include/Renderer/Shader.h"
#include "include/Camera.h"
#include "include/InputDispatcher.h"
#include "include/Light.h"
#include "include/Renderer/RenderingController.h"
#include "include/UI/UIManager.h"
#include "include/UI/UI_Component.h"

//给世界添加样品场景
void SceneExample()
{
    auto* world = GameInstance::Get()->world_;
    //生成地板
    LearnOpengl::Transform floor_transform = normalize_transform;
    floor_transform.position = gl_vec3{0.0, 0.0, 0.0};
    floor_transform.rotate = gl_vec3{-90.0f, 0.0f, 0.0f};
    floor_transform.scale = gl_vec3{3.0f, 3.0f, 3.0f};
    auto* floor = world->SpawnObject<Actor>(floor_transform);
    Model* floor_model = new Model("Resource/Model/floor/floor.fbx");
    floor->model_ = floor_model;

    //生成甘雨
    LearnOpengl::Transform gan_yv_transform = normalize_transform;
    gan_yv_transform.position = gl_vec3{0.0, 0.0, -0.5f};
    gan_yv_transform.rotate = gl_vec3{-90.0f, 0.0f, 0.0f};
    gan_yv_transform.scale = gl_vec3{0.5f, 0.5f, 0.5f};
    auto* gan_yv = world->SpawnObject<Actor>(gan_yv_transform);
    Model* gan_yv_model = new Model("Resource/Model/ganyv/gy.fbx");
    gan_yv->model_ = gan_yv_model;


    //生成神里绫华
    LearnOpengl::Transform shen_li_transform = normalize_transform;
    shen_li_transform.position = gl_vec3{0.0, 0.0, 0.0};
    shen_li_transform.rotate = gl_vec3{-90.0f, 0.0f, 0.0f};
    shen_li_transform.scale = gl_vec3{0.1f, 0.1f, 0.1f};
    auto* shen_li = world->SpawnObject<Actor>(shen_li_transform);
    Model* shen_li_model = new Model("Resource/Model/shenli/shenli.fbx");
    shen_li->model_ = shen_li_model;

    //生成玩家
    auto* player = dynamic_cast<Actor*>(world->SpawnObject<Actor>());
    Camera* camera = new Camera;
    player->AddCameraComponent(camera);
    world->player_ = player;

    //生成光照
    auto* dir_light = world->SpawnObject<DirLight>();
}

void UIExample()
{
    auto* ui_manager = UIManager::Get();
    ui_manager->CreateWindow("Rendering Setting");
    ui_manager->CreateComponent<RenderingSettingComponent>("Rendering Setting");
}

int main()
{
    // GameInstance初始化
    auto* game_instance = GameInstance::Get();
    auto* rendering_controller = RenderingController::Get();

    //SceneExample
    SceneExample();

    //UIExample
    UIExample();

    // 游戏循环
    while (!glfwWindowShouldClose(game_instance->window_))
    {
        //更新时间帧
        game_instance->UpdateFrame();
        glfwPollEvents();

        //处理输入事件
        InputDispatcher::HandleInputEvents(game_instance->window_);

        //游戏世界逻辑处理
        game_instance->world_->UpdateWorld(game_instance->delta_time_);

        //游戏世界渲染处理
        rendering_controller->RenderStart();

        //UI渲染处理
        UIManager::Get()->Update(game_instance->delta_time_);

        glfwSwapBuffers(game_instance->window_);
    }

    glfwTerminate();
    return 0;
}
