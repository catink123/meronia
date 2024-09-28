#include "EntityManager.h"

EntityManager::EntityManager() :
    m_entities(),
    m_drawableEntities(),
    m_updatableEntities()
{
}

const std::string EntityManager::RegisterEntity(std::shared_ptr<Entity> entity, std::optional<std::string> id)
{
    const std::string actualID = id.value_or(UUID::generate_uuid());
    if (m_entities.find(actualID) != std::end(m_entities))
    {
        throw EntityManager::EntityAlreadyRegisteredError("Entity with name '" + actualID + "' is already registered");
    }
    m_entities.insert({ actualID, entity });

    std::shared_ptr<DrawableEntity> drawable = std::dynamic_pointer_cast<DrawableEntity>(entity);
    if (drawable != nullptr)
    {
        m_drawableEntities.insert({ actualID, drawable });
    }
    std::shared_ptr<UpdatableEntity> updatable = std::dynamic_pointer_cast<UpdatableEntity>(entity);
    if (updatable != nullptr)
    {
        m_updatableEntities.insert({ actualID, updatable });
    }

    return actualID;
}

std::optional<const std::string> EntityManager::GetEntityID(std::shared_ptr<Entity> entity) const
{
    auto foundIt = std::find_if(std::begin(m_entities), std::end(m_entities), [&](auto entry) { return entity == entry.second; });
    if (foundIt != std::end(m_entities))
    {
        return foundIt->first;
    }
    return std::nullopt;
}

std::shared_ptr<Entity> EntityManager::GetEntity(const std::string& id)
{
    auto foundIt = m_entities.find(id);
    if (foundIt == std::end(m_entities))
    {
        throw EntityManager::EntityDoesntExistError("Entity with name '" + id + "' doesn't exist");
    }
    return foundIt->second;
}

const std::map<std::string, std::shared_ptr<Entity>>& EntityManager::GetEntities() const
{
    return m_entities;
}

const std::map<std::string, std::shared_ptr<DrawableEntity>>& EntityManager::GetDrawableEntities() const
{
    return m_drawableEntities;
}

const std::map<std::string, std::shared_ptr<UpdatableEntity>>& EntityManager::GetUpdatableEntities() const
{
    return m_updatableEntities;
}

void EntityManager::RemoveEntity(std::shared_ptr<Entity> entity)
{
    auto foundIt = std::find_if(std::begin(m_entities), std::end(m_entities), [&](auto entry) { return entity == entry.second; });
    if (foundIt != std::end(m_entities))
    {
        m_entities.erase(foundIt->first);
    }
}

void EntityManager::RemoveEntity(const std::string& id)
{
    if (m_entities.find(id) != std::end(m_entities))
    {
        m_entities.erase(id);
    }
}
