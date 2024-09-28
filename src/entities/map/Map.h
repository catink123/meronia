#pragma once
#include "../../base/Entity.h"
#include "MapData.h"
#include "../../base/CommonConstants.h"

class Map : public DrawableEntity, public UpdatableEntity
{
public:
    static const int TILE_SIZE = 10;

public:
    Map();

public:
    void Draw(const DrawContext& context) const override;
    void Update(const UpdateContext& context) override;

private:
    MapData m_data;
    sf::Vector2f m_offset;
};