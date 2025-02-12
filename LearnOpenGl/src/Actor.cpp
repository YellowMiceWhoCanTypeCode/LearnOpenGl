#include "../include/Actor.h"

#include "../include/Component.h"
#include "../include/Model.h"

using namespace LearnOpengl;

Actor::Actor()
{
}

Actor::Actor(const gl_vec3& position)
    : Object(position)
{
}

Actor::Actor(const Transform& transform)
    : Object(transform)
{
}

Actor::~Actor()
{
    for (auto* component : components_)
    {
        delete component;
    };
}

void Actor::Tick(float delta)
{
    Object::Tick(delta);
}

void Actor::Render(Shader* shader)
{
    for (auto* component : components_)
    {
        component->Render(shader);
    }
    if (model_ == nullptr)
        return;
    model_->Draw(shader, this);
}

Camera* Actor::GetCameraComponent()
{
    return camera_;
}

void Actor::AddCameraComponent(Camera* camera)
{
    this->camera_ = camera;
}
