#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "systems/EntityManager.h"
#include "Entity.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Engine
{
public:
    Engine();

    void Run();

private:
    void draw();
    void update(float deltaTime);

private:
    sf::RenderWindow m_window;
    sf::Clock m_frameClock;
    float m_lastFrameTime;

    sf::RectangleShape m_tempShape;
    sf::RectangleShape m_windowOutline;

    sf::Vector2u m_prevWindowSize;

    EntityManager m_entityManager;
};