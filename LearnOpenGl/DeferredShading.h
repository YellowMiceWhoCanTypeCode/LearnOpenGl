#pragma once

#include "Core.h"
#include "GLFW/glfw3.h"
#include <glad/glad.h>
#include "vendor/imgui/imgui_impl_opengl3_loader.h"

#include "include/Camera.h"
#include "Renderer/Shader.h"


extern unsigned int SCR_WIDTH, SCR_HEIGHT;
extern Camera camera;

class DeferredShading
{
public:
    DeferredShading() = default;
    ~DeferredShading() = default;

    void PreWork()
    {
        glGenFramebuffers(1, &gBuffer_);
        glBindFramebuffer(GL_FRAMEBUFFER, gBuffer_);

        //位置颜色缓冲
        glGenTextures(1, &gPoisition_);
        glBindTexture(GL_TEXTURE_2D, gPoisition_);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPoisition_, 0);

        //法线颜色缓冲
        glGenTextures(1, &gNormal_);
        glBindTexture(GL_TEXTURE_2D, gNormal_);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal_, 0);

        //颜色 + 镜面颜色缓冲
        glGenTextures(1, &gAlbedoSpec_);
        glBindTexture(GL_TEXTURE_2D, gAlbedoSpec_);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec_, 0);

        //告诉OpenGL我们将使用哪种颜色附件来进行渲染
        GLuint attachments[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
        glDrawBuffers(3, attachments);
    }


    void LoopWork()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderLightingPass_.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gPoisition_);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gNormal_);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, gAlbedoSpec_);

        //todo:发送光照相关的uniform

        shaderLightingPass_.setVec3("viewPos", camera.Position);
        RenderScene();
    }

public:
    Shader shaderLightingPass_;
    GLuint gBuffer_;
    GLuint gPoisition_;
    GLuint gNormal_;
    GLuint gAlbedoSpec_;
};
