#pragma once
#include <array>
#include "../../noise/SimplexNoise.hpp"

enum class Block : unsigned char
{
    Air = 0,
    Stone = 1,
    Grass = 2,
    Dirt = 3
};

class Chunk
{
public:
    static const unsigned int SIZE = 16;

public:
    Chunk();

public:
    void SetBlock(unsigned short x, unsigned short y, Block block);
    Block GetBlock(unsigned short x, unsigned short y) const;
    const std::array<Block, Chunk::SIZE * Chunk::SIZE>& GetData() const;

private:
    std::array<Block, Chunk::SIZE * Chunk::SIZE> m_data;
};

class MapData
{
public:
    static const unsigned int CHUNK_WIDTH = 12;
    static const unsigned int CHUNK_HEIGHT = 6;
    static const unsigned int CHUNK_COUNT = CHUNK_WIDTH * CHUNK_HEIGHT;

public:
    MapData();

public:
    void GenerateFromSeed(unsigned int seed);

public:
    void SetBlock(unsigned int x, unsigned int y, Block block);
    Block GetBlock(unsigned int x, unsigned int y) const;
    const std::array<Chunk, MapData::CHUNK_COUNT>& GetChunks() const;

private:
    std::array<Chunk, MapData::CHUNK_COUNT> m_chunks;
};