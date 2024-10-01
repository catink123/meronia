#pragma once
#include <array>
#include "../../noise/SimplexNoise.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../../base/CommonConstants.h"
#include "../../base/Helpers.h"

enum class Block : unsigned char
{
    Air = 0,
    Stone = 1,
    Grass = 2,
    Dirt = 3
};

class Chunk;

struct SurroundingChunkData
{
    const Chunk* leftTop;
    const Chunk* top;
    const Chunk* left;
};

class Chunk
{
public:
    static const unsigned int SIZE = 16;
    inline static const std::array<sf::IntRect, 16> TILE_CROPS =
    {
        sf::IntRect(0, 3 * CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE),
        sf::IntRect(1 * CommonConstants::TEXTURE_TILE_SIZE, 3 * CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE),
        sf::IntRect(0, 0, CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE),
        sf::IntRect(3 * CommonConstants::TEXTURE_TILE_SIZE, 0, CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE),
        sf::IntRect(0, 2 * CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE),
        sf::IntRect(1 * CommonConstants::TEXTURE_TILE_SIZE, 0, CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE),
        sf::IntRect(2 * CommonConstants::TEXTURE_TILE_SIZE, 3 * CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE),
        sf::IntRect(1 * CommonConstants::TEXTURE_TILE_SIZE, 1 * CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE),
        sf::IntRect(3 * CommonConstants::TEXTURE_TILE_SIZE, 3 * CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE),
        sf::IntRect(0, 1 * CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE),
        sf::IntRect(3 * CommonConstants::TEXTURE_TILE_SIZE, 2 * CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE),
        sf::IntRect(2 * CommonConstants::TEXTURE_TILE_SIZE, 0, CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE),
        sf::IntRect(1 * CommonConstants::TEXTURE_TILE_SIZE, 2 * CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE),
        sf::IntRect(2 * CommonConstants::TEXTURE_TILE_SIZE, 2 * CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE),
        sf::IntRect(3 * CommonConstants::TEXTURE_TILE_SIZE, 1 * CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE),
        sf::IntRect(2 * CommonConstants::TEXTURE_TILE_SIZE, 1 * CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE, CommonConstants::TEXTURE_TILE_SIZE)
    };

public:
    Chunk();

public:
    void SetBlock(unsigned short x, unsigned short y, Block block);
    Block GetBlock(unsigned short x, unsigned short y) const;
    const std::array<Block, Chunk::SIZE * Chunk::SIZE>& GetData() const;
    const sf::Sprite& GetSprite() const;
    void SetSpritePosition(const sf::Vector2f& position);

    void BuildTexture(const SurroundingChunkData& surroundingChunks);

private:
    unsigned char getExistingBlocks(unsigned short x, unsigned short y, const SurroundingChunkData& surroundingChunks);

private:
    std::array<Block, Chunk::SIZE * Chunk::SIZE> m_data;
    sf::RenderTexture m_texture;
    sf::Sprite m_sprite;
};

class MapData
{
public:
    static const unsigned int CHUNK_WIDTH = 48;
    static const unsigned int CHUNK_HEIGHT = 24;
    static const unsigned int CHUNK_COUNT = CHUNK_WIDTH * CHUNK_HEIGHT;

public:
    MapData();

public:
    void GenerateFromSeed(unsigned int seed);

public:
    void SetBlock(unsigned int x, unsigned int y, Block block);
    Block GetBlock(unsigned int x, unsigned int y) const;
    const std::array<Chunk, MapData::CHUNK_COUNT>& GetChunks() const;
    std::array<Chunk, MapData::CHUNK_COUNT>& GetChunksMut();

    void BuildChunkTextures();

public:
    static sf::Vector2i GetMapSize();

private:
    unsigned int xyToIndex(unsigned int x, unsigned int y) const;

private:
    std::array<Chunk, MapData::CHUNK_COUNT> m_chunks;
};