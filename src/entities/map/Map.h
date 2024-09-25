#pragma once
#include "../../base/Entity.h"
#include "MapData.h"

class Map : public DrawableEntity, public UpdatableEntity
{
public:
    Map();

public:
    void Draw(const DrawContext& context) const override;
    void Update(const UpdateContext& context) override;

private:
    MapData m_data;
};