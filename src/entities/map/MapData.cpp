#include "MapData.h"

Chunk::Chunk() :
    m_data()
{
}

void Chunk::SetBlock(unsigned short x, unsigned short y, Block block)
{
    m_data[x + y * Chunk::SIZE] = block;
}

Block Chunk::GetBlock(unsigned short x, unsigned short y) const
{
    return m_data[x + y * Chunk::SIZE];
}

const std::array<Block, Chunk::SIZE * Chunk::SIZE>& Chunk::GetData() const
{
    return m_data;
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

        double noiseValue = noise.unsignedFBM((double)x / 50, 0, 8, 2, 0.5);

        Block block = (noiseValue * 10 + mapHeight / 2) <= y ? Block::Stone : Block::Air;
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

sf::Vector2i MapData::GetMapSize()
{
    return sf::Vector2i(CHUNK_WIDTH * Chunk::SIZE, CHUNK_HEIGHT * Chunk::SIZE);
}
