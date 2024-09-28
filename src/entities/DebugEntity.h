#pragma once
#include "../base/Entity.h"
#include <SFML/Graphics.hpp>
#include "../base/CommonConstants.h"

class DebugEntity : public DrawableEntity
{
public:
    DebugEntity();

public:
    void Draw(const DrawContext& context) const override;

private:
    sf::RectangleShape m_windowOutline;
};