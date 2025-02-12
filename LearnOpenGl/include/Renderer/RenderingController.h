#pragma once
#include <string>
#include <vector>

class Light;

enum class Anti_Aliasing_Type
{
    MSAA = 0
};

class RenderingController
{
public:
    static RenderingController* Get();

    void AddLight(Light* light);

    void RenderStart();

protected:
    RenderingController();

    //深度缓冲生成
    void GenDepthBuffer();

public:
    bool enable_shadow_ = true;
    bool enable_ssao_ = false;
    bool enable_anti_aliasing_ = true;
    float far_plane_ = 100.f;
    Anti_Aliasing_Type anti_aliasing_type_ = Anti_Aliasing_Type::MSAA;

private:
    // all lights in world
    std::vector<Light*> lights_;

    //all shaders in game

    //depth_map_fbo and depth_map
    std::vector<std::pair<unsigned int, unsigned int>> depth_map_pairs_;

    std::string shadow_depth_shader_path_ = "Resource/Shaders/shadow_depth";
    std::string main_shader_path_ = "Resource/Shaders/main";
};
