#include "DebugEntity.h"

DebugEntity::DebugEntity() :
    m_tempShape(sf::Vector2f(100, 100)),
    m_windowOutline(sf::Vector2f(1280 - 10, 720 - 10))
{
    m_tempShape.setOrigin(sf::Vector2f(50, 50));
    m_tempShape.setPosition(sf::Vector2f(1280 / 2, 720 / 2));

    m_windowOutline.setPosition(sf::Vector2f(5, 5));
    m_windowOutline.setOutlineThickness(5);
    m_windowOutline.setOutlineColor(sf::Color::Red);
    m_windowOutline.setFillColor(sf::Color::Transparent);
}

void DebugEntity::Draw(const DrawContext& context) const
{
    context.window.draw(m_tempShape);
    //context.window.draw(m_windowOutline);
}

void DebugEntity::Update(const UpdateContext& context)
{
    m_tempShape.rotate(context.deltaTime * 50);
}
