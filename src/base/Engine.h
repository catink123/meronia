#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "systems/EntityManager.h"
#include "Entity.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../entities/DebugEntity.h"
#include "../entities/map/Map.h"

class Engine
{
public:
    static const unsigned int BASE_WIDTH = 1280;
    static const unsigned int BASE_HEIGHT = 720;

public:
    Engine();

public:
    void Run();

private:
    void draw();
    void update(float deltaTime);

private:
    sf::RenderWindow m_window;
    sf::Clock m_frameClock;
    float m_lastFrameTime;

    EntityManager m_entityManager;
};