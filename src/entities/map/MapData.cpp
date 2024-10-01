#include "MapData.h"

Chunk::Chunk() :
    m_data()
{
    m_texture.create(CommonConstants::TEXTURE_TILE_SIZE * (SIZE + 1), CommonConstants::TEXTURE_TILE_SIZE * (SIZE + 1));
    m_texture.clear(sf::Color::Transparent);
    m_sprite.setTexture(m_texture.getTexture());
}

void Chunk::SetBlock(unsigned short x, unsigned short y, Block block)
{
    m_data[x + y * Chunk::SIZE] = block;
}

inline Block Chunk::GetBlock(unsigned short x, unsigned short y) const
{
    return m_data[x + y * Chunk::SIZE];
}

const std::array<Block, Chunk::SIZE * Chunk::SIZE>& Chunk::GetData() const
{
    return m_data;
}

const sf::Sprite& Chunk::GetSprite() const
{
    return m_sprite;
}

void Chunk::SetSpritePosition(const sf::Vector2f& position)
{
    m_sprite.setPosition(position);
}

void Chunk::BuildTexture(const SurroundingChunkData& surroundingChunks)
{
    m_texture.clear(sf::Color::Transparent);

    sf::Texture grassTexture;
    if (!grassTexture.loadFromFile("assets/grassTexture.png"))
    {
        throw std::runtime_error("couldn't load grass texture");
    }
    sf::Sprite grassTextureSprite;
    grassTextureSprite.setTexture(grassTexture);

    for (int x = 0; x < SIZE; ++x)
    {
        for (int y = 0; y < SIZE; ++y)
        {
            unsigned char existingBlocks = getExistingBlocks(x, y, surroundingChunks);
            grassTextureSprite.setTextureRect(TILE_CROPS[existingBlocks]);
            grassTextureSprite.setPosition(sf::Vector2f(x * CommonConstants::TEXTURE_TILE_SIZE, y * CommonConstants::TEXTURE_TILE_SIZE));

            m_texture.draw(grassTextureSprite);
        }
    }
    m_texture.display();
}

unsigned char Chunk::getExistingBlocks(unsigned short x, unsigned short y, const SurroundingChunkData& surroundingChunks)
{
    unsigned char existingBlocks = 0;
    if (y == 0)
    {
        if (x == 0 && surroundingChunks.leftTop != nullptr && surroundingChunks.leftTop->GetBlock(SIZE - 1, SIZE - 1) != Block::Air)
        {
            existingBlocks |= CREATE_BIT(3);
        }
        else if (x > 0 && x <= SIZE - 1 && surroundingChunks.top != nullptr && surroundingChunks.top->GetBlock(x - 1, SIZE - 1) != Block::Air)
        {
            existingBlocks |= CREATE_BIT(3);
        }
    }
    else if (y <= SIZE - 1)
    {
        if (x == 0 && surroundingChunks.left != nullptr && surroundingChunks.left->GetBlock(SIZE - 1, y - 1) != Block::Air)
        {
            existingBlocks |= CREATE_BIT(3);
        }
        else if (x > 0 && x <= SIZE - 1 && GetBlock(x - 1, y - 1) != Block::Air)
        {
            existingBlocks |= CREATE_BIT(3);
        }
    }

    if (x <= SIZE - 1)
    {
        if (y == 0 && surroundingChunks.top != nullptr && surroundingChunks.top->GetBlock(x, SIZE - 1) != Block::Air)
        {
            existingBlocks |= CREATE_BIT(2);
        }
        else if (y > 0 && y <= SIZE - 1 && GetBlock(x, y - 1) != Block::Air)
        {
            existingBlocks |= CREATE_BIT(2);
        }
    }

    if (y <= SIZE - 1)
    {
        if (x == 0 && surroundingChunks.left != nullptr && surroundingChunks.left->GetBlock(SIZE - 1, y) != Block::Air)
        {
            existingBlocks |= CREATE_BIT(1);
        }
        if (x > 0 && x <= SIZE - 1 && GetBlock(x - 1, y) != Block::Air)
        {
            existingBlocks |= CREATE_BIT(1);
        }
    }

    if (x <= SIZE - 1 && y <= SIZE - 1 && GetBlock(x, y) != Block::Air)
    {
        existingBlocks |= CREATE_BIT(0);
    }

    return existingBlocks;
}

MapData::MapData() :
    m_chunks()
{
}

void MapData::GenerateFromSeed(unsigned int seed)
{
    SimplexNoise noise;
    noise.setSeed(seed);

    const unsigned int mapWidth = CHUNK_WIDTH * Chunk::SIZE;
    const unsigned int mapHeight = CHUNK_HEIGHT * Chunk::SIZE;

    for (unsigned int i = 0; i < CHUNK_COUNT * Chunk::SIZE * Chunk::SIZE; ++i)
    {
        const unsigned int x = i % mapWidth;
        const unsigned int y = i / mapWidth;

        double noiseValue = noise.unsignedFBM((double)x / 10, 0, 8, 1, 0.25);

        Block block = (noiseValue * 20 + mapHeight / 2) <= y ? Block::Stone : Block::Air;
        if (block != Block::Air)
        {
            printf("");
        }

        SetBlock(x, y, block);
    }
}

void MapData::SetBlock(unsigned int x, unsigned int y, Block block)
{
    unsigned int chunkX = x / Chunk::SIZE;
    unsigned int chunkY = y / Chunk::SIZE;
    unsigned int blockX = x % Chunk::SIZE;
    unsigned int blockY = y % Chunk::SIZE;

    m_chunks[chunkX + chunkY * CHUNK_WIDTH].SetBlock(blockX, blockY, block);
}

Block MapData::GetBlock(unsigned int x, unsigned int y) const
{
    unsigned int chunkX = x / Chunk::SIZE;
    unsigned int chunkY = y / Chunk::SIZE;
    unsigned int blockX = x % Chunk::SIZE;
    unsigned int blockY = y % Chunk::SIZE;

    return m_chunks[chunkX + chunkY * CHUNK_WIDTH].GetBlock(blockX, blockY);
}

const std::array<Chunk, MapData::CHUNK_COUNT>& MapData::GetChunks() const
{
    return m_chunks;
}

std::array<Chunk, MapData::CHUNK_COUNT>& MapData::GetChunksMut()
{
    return m_chunks;
}

void MapData::BuildChunkTextures()
{
    for (int x = 0; x < CHUNK_WIDTH; ++x)
    {
        for (int y = 0; y < CHUNK_HEIGHT; ++y)
        {
            SurroundingChunkData surrounding
            {
                x > 0 && y > 0 ? &m_chunks[xyToIndex(x - 1, y - 1)] : nullptr,
                y > 0 ? &m_chunks[xyToIndex(x, y - 1)] : nullptr,
                x > 0 ? &m_chunks[xyToIndex(x - 1, y)] : nullptr
            };
            m_chunks[x + y * CHUNK_WIDTH].BuildTexture(surrounding);
        }
    }
}

sf::Vector2i MapData::GetMapSize()
{
    return sf::Vector2i(CHUNK_WIDTH * Chunk::SIZE, CHUNK_HEIGHT * Chunk::SIZE);
}

inline unsigned int MapData::xyToIndex(unsigned int x, unsigned int y) const
{
    return x + y * CHUNK_WIDTH;
}
