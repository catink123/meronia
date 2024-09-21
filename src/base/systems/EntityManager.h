#pragma once
#include <map>
#include <memory>
#include <string>
#include <optional>
#include "../Helpers.h"
#include "uuid_v4.h"

class Entity;

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

    void RemoveEntity(std::shared_ptr<Entity> entity);
    void RemoveEntity(const std::string& id);

private:
    std::string generateID();

private:
    std::map<std::string, std::shared_ptr<Entity>> m_entities;
    UUIDv4::UUIDGenerator<std::mt19937> m_uuidGenerator;
};