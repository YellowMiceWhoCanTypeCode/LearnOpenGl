#include "../include/Component.h"

using namespace LearnOpengl;

Component::Component()
{
}

Component::Component(const Transform& relative_transform_)
    : Object(relative_transform_)
{
}

Component::~Component()
{
}
