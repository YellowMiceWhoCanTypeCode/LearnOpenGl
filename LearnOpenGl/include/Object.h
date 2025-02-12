#pragma once
#include "../Core.h"

class Shader;
class Model;

class Object
{
public:
    Object();
    Object(const gl_vec3& position);
    Object(const LearnOpengl::Transform& transform);
    virtual ~Object();


    //每帧调用接口
    virtual void Tick(float delta);

    //渲染接口
    virtual void Render(Shader* shader);

    //生成后调用
    virtual void AfterSpawn();

public:
    LearnOpengl::Transform transform_;

    //模型引用
    Model* model_ = nullptr;

protected:
};
