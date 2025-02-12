#include "../include/World.h"
#include "../include/Object.h"
#include "../include/Renderer/RenderingController.h"

World::~World()
{
    //世界销毁时，释放所有的object的内存
    for (auto* object : objects_)
    {
        delete object;
    }
}

void World::UpdateWorld(float delta)
{
    for (auto* object : objects_)
    {
        object->Tick(delta);
    }
}

void World::RenderScene(Shader* shader)
{
    //开始逐Object渲染
    for (auto* object : objects_)
    {
        object->Render(shader);
    }
}
