#pragma once
#include <SFML/Graphics.hpp>

class EntityManager;

struct DrawContext
{
    sf::RenderWindow& window;
    const sf::Vector2f& viewOffset;
};

struct UpdateContext
{
    float deltaTime;
    EntityManager& entityManager;
};