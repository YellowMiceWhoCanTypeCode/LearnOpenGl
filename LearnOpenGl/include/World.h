#pragma once
#include <vector>
#include "GameInstance.h"
#include "Object.h"

class Shader;
class Object;
class Actor;
class Camera;

class World
{
public:
    World() = default;
    ~World();

    //逻辑入口
    void UpdateWorld(float delta);

    //渲染场景
    void RenderScene(Shader* shader);

    //创建世界物品入口
    template <typename Type>
    static Object* SpawnObject(const LearnOpengl::Transform& transform = normalize_transform)
    {
        static_assert(std::is_base_of_v<Object, Type>, "Error:spawning object isn`t Object`s Child");
        Object* new_object = new Type(transform);
        new_object->AfterSpawn();
        auto* world = GameInstance::Get()->world_;
        world->objects_.push_back(new_object);
        return new_object;
    }

public:
    //玩家当前正在控制的actor
    Actor* player_;

private:
    //在世界场景中的所有物体的引用
    std::vector<Object*> objects_;
};
