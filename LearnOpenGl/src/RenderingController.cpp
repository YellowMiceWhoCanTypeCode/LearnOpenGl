#include "../include/Renderer/RenderingController.h"

#include <glad/glad.h>

#include "../include/Actor.h"
#include "../include/Camera.h"
#include "../include/GameInstance.h"
#include "../include/Light.h"
#include "../include/World.h"
#include "../include/Renderer/Shader.h"
#include "../vendor/spdlog/spdlog.h"

RenderingController* RenderingController::Get()
{
    static auto* rendering_controller = new RenderingController;
    return rendering_controller;
}

void RenderingController::AddLight(Light* light)
{
    lights_.push_back(light);
}

void RenderingController::RenderStart()
{
    //TODO:optimize->release the limit of the maximum number of light(also in fs)
    if (lights_.size() > 10)
    {
        spdlog::error("lights num over supported max light num");
        return;
    }
    auto* game_instance = GameInstance::Get();
    auto* world = game_instance->world_;
    auto* camera = world->player_->GetCameraComponent();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto* simpleDepthShader = new Shader(shadow_depth_shader_path_ + ".vs.glsl", shadow_depth_shader_path_ + ".fs.glsl");

    //渲染深度至纹理
    for (unsigned int i = 0; i < lights_.size(); ++i)
    {
        simpleDepthShader->use();
        const auto& light_space_mat = lights_[i]->GetLightSpaceMatrix(far_plane_);
        simpleDepthShader->setMat4("light_space_matrix", light_space_mat);
        //TODO:GenDepthBuffer每一帧都会生成帧缓冲，如何让它只生成一次？
        GenDepthBuffer();

        glViewport(0, 0, 1024, 1024);
        glBindFramebuffer(GL_FRAMEBUFFER, depth_map_pairs_[i].first);
        glClear(GL_DEPTH_BUFFER_BIT);

        world->RenderScene(simpleDepthShader);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    //使用深度图开始渲染场景
    auto* mainShader = new Shader(main_shader_path_ + ".vs.glsl", main_shader_path_ + ".fs.glsl");
    mainShader->use();
    const auto& view = camera->GetViewMatrix();
    const auto& projection = glm::perspective(glm::radians(camera->Zoom), (float)game_instance->window_width_ / (float)game_instance->window_height_, 0.1f, camera->zFar);
    mainShader->setMat4("view", view);
    mainShader->setMat4("projection", projection);

    /*GLuint shadow_map_array;
    glGenTextures(1, &shadow_map_array);
    glBindBuffer(GL_TEXTURE_2D_ARRAY, shadow_map_array);*/


    //TODO:set shadow map to mainShader
    world->RenderScene(mainShader);
}

RenderingController::RenderingController()
{
    spdlog::info("RenderingController init begin!");
    spdlog::info("RenderingController init end!");
}

void RenderingController::GenDepthBuffer()
{
    GLuint depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);

    GLuint depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat borderColor[] = {1.0, 1.0, 1.0, 1.0};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    depth_map_pairs_.emplace_back(depthMapFBO, depthMap);
}
