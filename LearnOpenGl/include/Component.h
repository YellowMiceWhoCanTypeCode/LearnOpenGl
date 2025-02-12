#pragma once
#include "Object.h"

class Component : public Object
{
public:
    Component();
    Component(const LearnOpengl::Transform& relative_transform_);

    virtual ~Component();

public:
    //继承自Object，Object的transform_成员变量在Component中表示相对于附加Actor的变换
};
