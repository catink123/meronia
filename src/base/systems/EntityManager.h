#pragma once
#include <map>
#include <memory>
#include <string>
#include <optional>
#include "../Helpers.h"
#include "UUIDGenerator.h"
#include "../Entity.h"
#include <vector>
#include <utility>

class EntityManager
{
public:
    DECLARE_RUNTIME_ERROR(EntityAlreadyRegisteredError)
    DECLARE_RUNTIME_ERROR(EntityDoesntExistError)

public:
    EntityManager();

public:
    const std::string RegisterEntity(std::shared_ptr<Entity> entity, std::optional<std::string> id = std::nullopt);
    std::optional<const std::string> GetEntityID(std::shared_ptr<Entity> entity) const;
    std::shared_ptr<Entity> GetEntity(const std::string& id);
    const UnsortedMap<std::string, std::shared_ptr<Entity>>& GetEntities() const;
    const UnsortedMap<std::string, std::shared_ptr<DrawableEntity>>& GetDrawableEntities() const;
    const UnsortedMap<std::string, std::shared_ptr<UpdatableEntity>>& GetUpdatableEntities() const;

    void RemoveEntity(std::shared_ptr<Entity> entity);
    void RemoveEntity(const std::string& id);

private:
    UnsortedMap<std::string, std::shared_ptr<Entity>> m_entities;
    UnsortedMap<std::string, std::shared_ptr<DrawableEntity>> m_drawableEntities;
    UnsortedMap<std::string, std::shared_ptr<UpdatableEntity>> m_updatableEntities;

private:
    using EntitiesFinder = UnsortedMapFinder<decltype(m_entities)>;
    using DrawableEntitiesFinder = UnsortedMapFinder<decltype(m_drawableEntities)>;
    using UpdatableEntitiesFinder = UnsortedMapFinder<decltype(m_updatableEntities)>;
};