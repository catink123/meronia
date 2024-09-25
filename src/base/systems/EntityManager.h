#pragma once
#include <map>
#include <memory>
#include <string>
#include <optional>
#include "../Helpers.h"
#include "uuid_v4.h"
#include "../Entity.h"

class EntityManager
{
public:
    DECLARE_RUNTIME_ERROR(EntityAlreadyRegisteredError);
    DECLARE_RUNTIME_ERROR(EntityDoesntExistError);

public:
    EntityManager();

public:
    const std::string RegisterEntity(std::shared_ptr<Entity> entity, std::optional<std::string> id = std::nullopt);
    std::optional<const std::string> GetEntityID(std::shared_ptr<Entity> entity) const;
    std::shared_ptr<Entity> GetEntity(const std::string& id);
    const std::map<std::string, std::shared_ptr<Entity>>& GetEntities() const;
    const std::map<std::string, std::shared_ptr<DrawableEntity>>& GetDrawableEntities() const;
    const std::map<std::string, std::shared_ptr<UpdatableEntity>>& GetUpdatableEntities() const;

    void RemoveEntity(std::shared_ptr<Entity> entity);
    void RemoveEntity(const std::string& id);

private:
    std::string generateID();

private:
    std::map<std::string, std::shared_ptr<Entity>> m_entities;
    std::map<std::string, std::shared_ptr<DrawableEntity>> m_drawableEntities;
    std::map<std::string, std::shared_ptr<UpdatableEntity>> m_updatableEntities;
    UUIDv4::UUIDGenerator<std::mt19937> m_uuidGenerator;
};