#pragma once
#include <SFML/Graphics.hpp>

class EntityManager;

struct DrawContext
{
    sf::RenderWindow& window;
};

struct UpdateContext
{
    float deltaTime;
    EntityManager& entityManager;
};