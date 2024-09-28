#include "Map.h"

Map::Map() :
    m_data(),
    m_offset()
{
    m_data.GenerateFromSeed(0);

    sf::Vector2i actualMapSize = MapData::GetMapSize() * TILE_SIZE;
    m_offset = sf::Vector2f((float)CommonConstants::WINDOW_BASE_WIDTH / 2 - (float)actualMapSize.x / 2, (float)CommonConstants::WINDOW_BASE_HEIGHT / 2 - (float)actualMapSize.y / 2);
}

void Map::Draw(const DrawContext& context) const
{
    sf::RectangleShape drawRect(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    sf::FloatRect cullingRect(-context.viewOffset - drawRect.getSize(), context.window.getView().getSize() + drawRect.getSize());

    const auto& chunks = m_data.GetChunks();
    for (unsigned int x = 0; x < MapData::CHUNK_WIDTH * Chunk::SIZE; ++x)
    {
        for (unsigned int y = 0; y < MapData::CHUNK_HEIGHT * Chunk::SIZE; ++y)
        {
            sf::Vector2f position(x * TILE_SIZE + m_offset.x, y * TILE_SIZE + m_offset.y);
            if (cullingRect.contains(position) && m_data.GetBlock(x, y) != Block::Air)
            {
                drawRect.setPosition(position);
                context.window.draw(drawRect);
            }
        }
    }
}

void Map::Update(const UpdateContext& context)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_offset.x += 200 * context.deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_offset.x -= 200 * context.deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_offset.y -= 200 * context.deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_offset.y += 200 * context.deltaTime;
    }
}
