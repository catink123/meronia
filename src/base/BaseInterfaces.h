#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Contexts.h"

class IUpdatable
{
public:
    virtual void Update(const UpdateContext& context) = 0;
};

class IDrawable
{
public:
    virtual void Draw(const DrawContext& context) const = 0;
};