#pragma once

class IUpdatable
{
public:
    virtual void Update(const float& deltaT) = 0;
};

class IDrawable
{
public:
    virtual void Draw() = 0;
};