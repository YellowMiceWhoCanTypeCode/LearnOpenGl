#pragma once

class UI_Component
{
public:
    UI_Component();

    virtual void Render() = 0;
};

class RenderingSettingComponent : public UI_Component
{
public:
    RenderingSettingComponent();

    void Render() override;

public:
};
