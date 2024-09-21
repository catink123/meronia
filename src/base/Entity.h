#pragma once
#include <memory>
#include "BaseInterfaces.h"

class Entity : std::enable_shared_from_this<Entity>
{
public:
    virtual ~Entity()
    {
    }
};

class DrawableEntity : public Entity, public IDrawable
{
public:
    virtual void Draw() override = 0;
};

class UpdatableEntity : public Entity, public IUpdatable
{
public:
    virtual void Update(const float& deltaT) override = 0;
};