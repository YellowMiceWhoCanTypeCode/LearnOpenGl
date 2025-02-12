#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "../vendor/imgui/imgui_internal.h"


// 定义资源结构体
struct Resource
{
    std::string name; // 资源名称
    std::string path; // 文件路径
    std::string type; // 资源类型 (Texture, Model, Audio)
    bool is_directory; // 是否是文件夹
    std::vector<Resource> children; // 子资源
};

// 示例资源数据
inline std::vector<Resource> resource_list = {
    {
        "Images", "Resource/", "Folder", true, {
            {"BrickTexture.png", "assets/textures/BrickTexture.png", "Texture", false, {}},
            {"GrassTexture.png", "assets/textures/GrassTexture.png", "Texture", false, {}}
        }
    },
    {
        "Model", "Resource/", "Folder", true, {
            {"HouseModel.obj", "assets/models/HouseModel.obj", "Model", false, {}},
            {"CarModel.obj", "assets/models/CarModel.obj", "Model", false, {}}
        }
    },
    {
        "Shaders", "Resource/", "Folder", true, {
            {"BackgroundMusic.mp3", "assets/audio/BackgroundMusic.mp3", "Audio", false, {}}
        }
    }
};

// 全局变量
inline Resource* selected_resource = nullptr; // 当前选中的资源
inline char search_filter[128] = ""; // 搜索关键字

// 递归渲染资源树
void RenderResourceTree(const Resource& resource)
{
    if (resource.is_directory)
    {
        if (ImGui::TreeNode(resource.name.c_str()))
        {
            for (const auto& child : resource.children)
            {
                RenderResourceTree(child); // 递归渲染子资源
            }
            ImGui::TreePop();
        }
    }
    else
    {
        if (ImGui::Selectable(resource.name.c_str(), selected_resource == &resource))
        {
            selected_resource = const_cast<Resource*>(&resource); // 更新选中的资源
        }

        // 拖拽支持
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
        {
            ImGui::SetDragDropPayload("RESOURCE", resource.path.c_str(), resource.path.size() + 1);
            ImGui::Text("Dragging: %s", resource.name.c_str());
            ImGui::EndDragDropSource();
        }
    }
}

// 搜索资源并显示
void RenderFilteredResources(const std::vector<Resource>& resources)
{
    for (const auto& resource : resources)
    {
        if (resource.is_directory)
        {
            RenderFilteredResources(resource.children); // 递归查找文件夹
        }
        else if (resource.name.find(search_filter) != std::string::npos)
        {
            if (ImGui::Selectable(resource.name.c_str(), selected_resource == &resource))
            {
                selected_resource = const_cast<Resource*>(&resource);
            }
        }
    }
}

// 资源预览窗口
void RenderResourcePreview()
{
    ImGui::Begin("Resource Preview");
    if (selected_resource)
    {
        ImGui::Text("Name: %s", selected_resource->name.c_str());
        ImGui::Text("Path: %s", selected_resource->path.c_str());
        ImGui::Text("Type: %s", selected_resource->type.c_str());
        if (selected_resource->type == "Texture")
        {
            // 示例显示缩略图 (需要实际绑定纹理)
            ImGui::Text("[Texture Preview Here]");
        }
        else if (selected_resource->type == "Model")
        {
            ImGui::Text("[Model Preview Here]");
        }
        else if (selected_resource->type == "Audio")
        {
            ImGui::Text("[Audio Preview Here]");
        }
    }
    else
    {
        ImGui::Text("No resource selected.");
    }
    ImGui::End();
}

// 主渲染函数
void RenderResourceBrowser()
{
    ImGui::Begin("Resource Browser");

    // 搜索栏
    ImGui::InputText("Search", search_filter, IM_ARRAYSIZE(search_filter));

    // 显示资源
    if (strlen(search_filter) > 0)
    {
        RenderFilteredResources(resource_list);
    }
    else
    {
        for (const auto& resource : resource_list)
        {
            RenderResourceTree(resource);
        }
    }

    ImGui::End();

    // 渲染资源预览窗口
    RenderResourcePreview();
}

// 示例主循环
void MainLoop()
{
    // 初始化 ImGui 上下文等（此处省略初始化代码）

    while (true)
    {
        // 开始新帧
        ImGui::NewFrame();

        // 渲染资源浏览器
        RenderResourceBrowser();

        // 结束帧并渲染（具体实现依赖于你的渲染器）
        ImGui::Render();
    }
}
