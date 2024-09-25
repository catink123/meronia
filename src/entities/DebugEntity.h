#pragma once
#include "../base/Entity.h"
#include <SFML/Graphics.hpp>

class DebugEntity : public DrawableEntity, public UpdatableEntity
{
public:
    DebugEntity();

public:
    void Draw(const DrawContext& context) const override;
    void Update(const UpdateContext& context) override;

private:
    sf::RectangleShape m_tempShape;
    sf::RectangleShape m_windowOutline;
};