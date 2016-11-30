#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace fgm {


enum class TileType { LAVA, DIRT, GRASS, STONE };

class TileTextureProvider {
public:
  TileTextureProvider();

  TileTextureProvider(const TileTextureProvider&) = delete;
  TileTextureProvider& operator=(const TileTextureProvider&) = delete;
  TileTextureProvider(TileTextureProvider&&) = default;
  TileTextureProvider& operator=(TileTextureProvider&&) = default;

  sf::Texture& getTileTexture(const TileType tileType);

private:
  std::unordered_map<TileType, sf::Texture> tileSpriteMap_;
};
}
