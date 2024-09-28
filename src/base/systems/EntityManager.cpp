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
    if (EntitiesFinder::FindByKey(m_entities, actualID) != std::end(m_entities))
    {
        throw EntityManager::EntityAlreadyRegisteredError("Entity with name '" + actualID + "' is already registered");
    }
    m_entities.push_back({ actualID, entity });

    std::shared_ptr<DrawableEntity> drawable = std::dynamic_pointer_cast<DrawableEntity>(entity);
    if (drawable != nullptr)
    {
        m_drawableEntities.push_back({ actualID, drawable });
    }
    std::shared_ptr<UpdatableEntity> updatable = std::dynamic_pointer_cast<UpdatableEntity>(entity);
    if (updatable != nullptr)
    {
        m_updatableEntities.push_back({ actualID, updatable });
    }

    return actualID;
}

std::optional<const std::string> EntityManager::GetEntityID(std::shared_ptr<Entity> entity) const
{
    auto foundIt = EntitiesFinder::FindByValue(m_entities, entity);
    if (foundIt != std::end(m_entities))
    {
        return foundIt->first;
    }
    return std::nullopt;
}

std::shared_ptr<Entity> EntityManager::GetEntity(const std::string& id)
{
    auto foundIt = EntitiesFinder::FindByKey(m_entities, id);
    if (foundIt == std::end(m_entities))
    {
        throw EntityManager::EntityDoesntExistError("Entity with name '" + id + "' doesn't exist");
    }
    return foundIt->second;
}

const UnsortedMap<std::string, std::shared_ptr<Entity>>& EntityManager::GetEntities() const
{
    return m_entities;
}

const UnsortedMap<std::string, std::shared_ptr<DrawableEntity>>& EntityManager::GetDrawableEntities() const
{
    return m_drawableEntities;
}

const UnsortedMap<std::string, std::shared_ptr<UpdatableEntity>>& EntityManager::GetUpdatableEntities() const
{
    return m_updatableEntities;
}

void EntityManager::RemoveEntity(std::shared_ptr<Entity> entity)
{
    auto foundIt = EntitiesFinder::FindByValue(m_entities, entity);
    if (foundIt != std::end(m_entities))
    {
        m_entities.erase(foundIt);
    }

    auto drawableEntity = std::dynamic_pointer_cast<DrawableEntity>(entity);
    if (drawableEntity != nullptr)
    {
        auto drawableFoundIt = DrawableEntitiesFinder::FindByValue(m_drawableEntities, drawableEntity);
        if (drawableFoundIt != std::end(m_drawableEntities))
        {
            m_drawableEntities.erase(drawableFoundIt);
        }
    }

    auto updatableEntity = std::dynamic_pointer_cast<UpdatableEntity>(entity);
    if (updatableEntity != nullptr)
    {
        auto updatableFoundIt = UpdatableEntitiesFinder::FindByValue(m_updatableEntities, updatableEntity);
        if (updatableFoundIt != std::end(m_updatableEntities))
        {
            m_updatableEntities.erase(updatableFoundIt);
        }
    }
}

void EntityManager::RemoveEntity(const std::string& id)
{
    auto foundIt = EntitiesFinder::FindByKey(m_entities, id);
    if (foundIt != std::end(m_entities))
    {
        m_entities.erase(foundIt);
    }

    auto drawableFoundIt = DrawableEntitiesFinder::FindByKey(m_drawableEntities, id);
    if (drawableFoundIt != std::end(m_drawableEntities))
    {
        m_drawableEntities.erase(drawableFoundIt);
    }

    auto updatableFoundIt = UpdatableEntitiesFinder::FindByKey(m_updatableEntities, id);
    if (updatableFoundIt != std::end(m_updatableEntities))
    {
        m_updatableEntities.erase(updatableFoundIt);
    }
}
