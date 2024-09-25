#pragma once
#include <memory>
#include "BaseInterfaces.h"

class Entity : public std::enable_shared_from_this<Entity>
{
public:
    virtual ~Entity()
    {
    }

public:
    std::shared_ptr<Entity> GetBase()
    {
        return std::dynamic_pointer_cast<Entity>(shared_from_this());
    }
};

class DrawableEntity : public virtual Entity, public IDrawable
{
public:
    virtual void Draw(const DrawContext& context) const override = 0;
};

class UpdatableEntity : public virtual Entity, public IUpdatable
{
public:
    virtual void Update(const UpdateContext& context) override = 0;
};