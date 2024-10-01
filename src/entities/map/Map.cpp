#include "Map.h"

Map::Map() :
    m_data(),
    m_offset()
{
    m_data.GenerateFromSeed(0);
    m_data.BuildChunkTextures();

    sf::Vector2i actualMapSize = MapData::GetMapSize() * TILE_SIZE;
    m_offset = sf::Vector2f((float)CommonConstants::WINDOW_BASE_WIDTH / 2 - (float)actualMapSize.x / 2, (float)CommonConstants::WINDOW_BASE_HEIGHT / 2 - (float)actualMapSize.y / 2);

    auto& chunks = m_data.GetChunksMut();
    for (unsigned int x = 0; x < MapData::CHUNK_WIDTH; ++x)
    {
        for (unsigned int y = 0; y < MapData::CHUNK_HEIGHT; ++y)
        {
            chunks[x + y * MapData::CHUNK_WIDTH].SetSpritePosition(sf::Vector2f(Chunk::SIZE * x * CommonConstants::TEXTURE_TILE_SIZE, Chunk::SIZE * y * CommonConstants::TEXTURE_TILE_SIZE) + m_offset - (sf::Vector2f(.5f, .5f) * (float)CommonConstants::TEXTURE_TILE_SIZE));
        }
    }
}

void Map::Draw(const DrawContext& context) const
{
    float actualChunkSize = Chunk::SIZE * CommonConstants::TEXTURE_TILE_SIZE;
    sf::FloatRect cullingRect(-context.viewOffset - sf::Vector2f(actualChunkSize, actualChunkSize), context.window.getView().getSize() + sf::Vector2f(actualChunkSize, actualChunkSize));

    const auto& chunks = m_data.GetChunks();

    for (unsigned int x = 0; x < MapData::CHUNK_WIDTH; ++x)
    {
        for (unsigned int y = 0; y < MapData::CHUNK_HEIGHT; ++y)
        {
            sf::Vector2f transformedPosition((float)x * CommonConstants::TEXTURE_TILE_SIZE * Chunk::SIZE + m_offset.x, (float)y * CommonConstants::TEXTURE_TILE_SIZE * Chunk::SIZE + m_offset.y);
            if (cullingRect.contains(transformedPosition))
            {
                const sf::Sprite& sprite = chunks[x + y * MapData::CHUNK_WIDTH].GetSprite();
                context.window.draw(sprite);
            }
        }
    }
}

void Map::Update(const UpdateContext& context)
{
    bool offsetChanged = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_offset.x -= 500 * context.deltaTime;
        offsetChanged = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_offset.x += 500 * context.deltaTime;
        offsetChanged = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_offset.y += 500 * context.deltaTime;
        offsetChanged = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_offset.y -= 500 * context.deltaTime;
        offsetChanged = true;
    }

    if (offsetChanged)
    {
        auto& chunks = m_data.GetChunksMut();

        for (unsigned int x = 0; x < MapData::CHUNK_WIDTH; ++x)
        {
            for (unsigned int y = 0; y < MapData::CHUNK_HEIGHT; ++y)
            {
                chunks[x + y * MapData::CHUNK_WIDTH].SetSpritePosition(sf::Vector2f(Chunk::SIZE * x * CommonConstants::TEXTURE_TILE_SIZE, Chunk::SIZE * y * CommonConstants::TEXTURE_TILE_SIZE) + m_offset - (sf::Vector2f(.5f, .5f) * (float)CommonConstants::TEXTURE_TILE_SIZE));
            }
        }
    }
}
