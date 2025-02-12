#include "../include/Object.h"

#include "../include/Model.h"

using namespace LearnOpengl;

Object::Object()
    : transform_(normalize_transform)
{
}

Object::Object(const gl_vec3& position)
    : transform_(normalize_transform)
{
    transform_.position = position;
}

Object::Object(const Transform& transform)
    : transform_(transform)
{
}

Object::~Object()
{
    delete model_;
}

void Object::Tick(float delta)
{
}

void Object::Render(Shader* shader)
{
    if (model_ == nullptr)
        return;
    model_->Draw(shader, this);
}

void Object::AfterSpawn()
{
}
