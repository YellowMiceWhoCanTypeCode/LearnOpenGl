#pragma once
#include <vector>

#include "../include/Object.h"

class Model;
class Camera;
class Component;

class Actor : public Object
{
public:
    Actor();
    Actor(const gl_vec3& position);
    Actor(const LearnOpengl::Transform& transform);
    virtual ~Actor();

    void Tick(float delta) override;

    void Render(Shader* shader) override;


    Camera* GetCameraComponent();
    void AddCameraComponent(Camera* camera);

private:
    //相机
    Camera* camera_ = nullptr;

    //actor身上装配的所有的Component
    std::vector<Component*> components_;
};
