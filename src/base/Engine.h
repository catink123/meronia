#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "systems/EntityManager.h"
#include "Entity.h"

class Engine
{
public:
    Engine();

    void Run();

private:
    sf::RenderWindow m_window;

    EntityManager m_entityManager;
};