#include "DebugEntity.h"

DebugEntity::DebugEntity() :
    m_windowOutline(sf::Vector2f(CommonConstants::WINDOW_BASE_WIDTH - 10, CommonConstants::WINDOW_BASE_HEIGHT - 10))
{
    m_windowOutline.setPosition(sf::Vector2f(5, 5));
    m_windowOutline.setOutlineThickness(5);
    m_windowOutline.setOutlineColor(sf::Color::Red);
    m_windowOutline.setFillColor(sf::Color::Transparent);
}

void DebugEntity::Draw(const DrawContext& context) const
{
    context.window.draw(m_windowOutline);
}
