#include "Engine.h"

Engine::Engine() :
    m_window(sf::VideoMode(640, 480), "Title", sf::Style::Default, sf::ContextSettings(0, 0, 8, 1, 1, 0, false)),
    m_entityManager(),
    m_tempShape(sf::Vector2f(100, 100)),
    m_windowOutline(sf::Vector2f(640 - 10, 480 - 10)),
    m_lastFrameTime(0),
    m_prevWindowSize(640, 480)
{
    m_tempShape.setOrigin(sf::Vector2f(50, 50));
    m_tempShape.setPosition(sf::Vector2f(320, 240));

    m_windowOutline.setPosition(sf::Vector2f(5, 5));
    m_windowOutline.setOutlineThickness(5);
    m_windowOutline.setOutlineColor(sf::Color::Red);
    m_windowOutline.setFillColor(sf::Color::Transparent);
}

void Engine::Run()
{
    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }
            if (event.type == sf::Event::Resized)
            {
                double newAspectRatio = (double)event.size.width / (double)event.size.height;

                m_window.setView(sf::View(sf::FloatRect(0, 0, (640 / (4 / 3)) * newAspectRatio, 480)));
            }
        }

        float elapsedTime = m_frameClock.getElapsedTime().asSeconds();
        float deltaTime = elapsedTime - m_lastFrameTime;
        m_lastFrameTime = elapsedTime;

        update(deltaTime);
        draw();
    }
}

void Engine::draw()
{
    m_window.clear();

    m_window.draw(m_tempShape);
    m_window.draw(m_windowOutline);

    m_window.display();
}

void Engine::update(float deltaTime)
{
    m_tempShape.rotate(deltaTime * 50);
}

