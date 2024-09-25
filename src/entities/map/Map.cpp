#include "Map.h"

Map::Map() :
    m_data()
{
    m_data.GenerateFromSeed(0);
}

void Map::Draw(const DrawContext& context) const
{
    sf::RectangleShape drawRect(sf::Vector2f(1, 1));

    const auto& chunks = m_data.GetChunks();
    for (unsigned int x = 0; x < MapData::CHUNK_WIDTH * Chunk::SIZE; ++x)
    {
        for (unsigned int y = 0; y < MapData::CHUNK_HEIGHT * Chunk::SIZE; ++y)
        {
            if (m_data.GetBlock(x, y) != Block::Air)
            {
                drawRect.setPosition(sf::Vector2f(x, y));
                context.window.draw(drawRect);
            }
        }
    }
}

void Map::Update(const UpdateContext& context)
{
}
