#include "Engine.h"

Engine::Engine() :
    m_window(sf::VideoMode(CommonConstants::WINDOW_BASE_WIDTH, CommonConstants::WINDOW_BASE_HEIGHT), CommonConstants::GAME_TITLE, sf::Style::Default, sf::ContextSettings(0, 0, 8, 1, 1, 0, false)),
    m_entityManager(),
    m_frameClock(),
    m_lastFrameTime(0),
    m_viewOffset()
{
    m_entityManager.RegisterEntity(std::make_shared<Map>()->GetBase(), "map");
    m_entityManager.RegisterEntity(std::make_shared<DebugEntity>()->GetBase(), "debug");
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
            else if (event.type == sf::Event::Resized)
            {
                double newAspectRatio = (double)event.size.width / (double)event.size.height;

                float viewWidth;
                float viewHeight;
                if (newAspectRatio > (float)CommonConstants::WINDOW_BASE_WIDTH / (float)CommonConstants::WINDOW_BASE_HEIGHT)
                {
                    viewWidth = (float)CommonConstants::WINDOW_BASE_HEIGHT * newAspectRatio;
                    viewHeight = (float)CommonConstants::WINDOW_BASE_HEIGHT;
                }
                else
                {
                    viewWidth = (float)CommonConstants::WINDOW_BASE_WIDTH;
                    viewHeight = (float)CommonConstants::WINDOW_BASE_WIDTH / newAspectRatio;
                }

                float viewOffsetX = -(viewWidth / 2 - CommonConstants::WINDOW_BASE_WIDTH / 2);
                float viewOffsetY = -(viewHeight / 2 - CommonConstants::WINDOW_BASE_HEIGHT / 2);
                m_viewOffset = sf::Vector2f(-viewOffsetX, -viewOffsetY);

                m_window.setView(sf::View(sf::FloatRect(viewOffsetX, viewOffsetY, viewWidth, viewHeight)));
            }
            else
            {
                switch (event.type)
                {
                case sf::Event::KeyPressed:             handleKeyPressed(event.key);                    break;
                case sf::Event::KeyReleased:            handleKeyReleased(event.key);                   break;
                case sf::Event::MouseMoved:             handleMouseMoved(event.mouseMove);              break;
                case sf::Event::MouseButtonPressed:     handleMouseButtonPressed(event.mouseButton);    break;
                case sf::Event::MouseButtonReleased:    handleMouseButtonReleased(event.mouseButton);   break;
                case sf::Event::MouseEntered:           handleMouseEntered();                           break;
                case sf::Event::MouseLeft:              handleMouseLeft();                              break;
                case sf::Event::MouseWheelScrolled:     handleMouseScrolled(event.mouseWheelScroll);    break;
                }
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
    DrawContext context{ m_window, m_viewOffset };

    m_window.clear();

    const auto& entities = m_entityManager.GetDrawableEntities();
    for (const auto& entry : entities)
    {
        entry.second->Draw(context);
    }

    m_window.display();
}

void Engine::update(float deltaTime)
{
    UpdateContext context{ deltaTime, m_entityManager };

    const auto& entities = m_entityManager.GetUpdatableEntities();
    for (const auto& entry : entities)
    {
        entry.second->Update(context);
    }
}

void Engine::handleKeyPressed(const sf::Event::KeyEvent& e)
{
}

void Engine::handleKeyReleased(const sf::Event::KeyEvent& e)
{
}

void Engine::handleMouseButtonPressed(const sf::Event::MouseButtonEvent& e)
{
}

void Engine::handleMouseButtonReleased(const sf::Event::MouseButtonEvent& e)
{
}

void Engine::handleMouseLeft()
{
}

void Engine::handleMouseEntered()
{
}

void Engine::handleMouseMoved(const sf::Event::MouseMoveEvent& e)
{
}

void Engine::handleMouseScrolled(const sf::Event::MouseWheelScrollEvent& e)
{
}

