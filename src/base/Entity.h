#pragma once
#include <memory>
#include "BaseInterfaces.h"
#include <unordered_map>
#include "Helpers.h"

class Entity : public std::enable_shared_from_this<Entity>
{
public:
    virtual ~Entity()
    {
    }

public:
    std::shared_ptr<Entity> GetBase()
    {
        return std::static_pointer_cast<Entity>(shared_from_this());
    }
    
    const std::string& GetName()
    {
        return m_name;
    }

private:
    std::string m_name;
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