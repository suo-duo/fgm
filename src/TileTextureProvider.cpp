#include "TileTextureProvider.h"

#include <boost/filesystem.hpp>
#include <folly/Singleton.h>

namespace {

static const std::string tilePath = "./assets/img/tiles/";
folly::Singleton<TileTextureProvider> tileTextureProvider([]() {
  return new TileTextureProvider();
});
}

TileTextureProvider::TileTextureProvider() {
  // Get the path to the tile images on disk
  const auto path = boost::filesystem::path(tilePath);
  auto dirIter = boost::filesystem::directory_iterator(path);
  for (const auto dirEntry : dirIter) {
    const auto path = dirEntry.path();
    if (boost::filesystem::is_regular_file(path) &&
        // only use png files
        path.string().find("png") != std::string::npos) {
      // Load texture
      sf::Texture texture;
      if (!texture.loadFromFile(path.string())) {
        throw std::runtime_error("Failed to load texture from path: " +
                                 path.string());
      }

      // Build the tileType map
      TileType tileType;
      const auto fileName = path.filename().string();
      if (fileName == "lava.png") {
        assert(tileSpriteMap_.count(TileType::LAVA) == 0);
        tileSpriteMap_[TileType::LAVA] = std::move(texture);
      } else if (fileName == "dirt.png") {
        assert(tileSpriteMap_.count(TileType::DIRT) == 0);
        tileSpriteMap_[TileType::DIRT] = std::move(texture);
      } else if (fileName == "grass.png") {
        assert(tileSpriteMap_.count(TileType::GRASS) == 0);
        tileSpriteMap_[TileType::GRASS] = std::move(texture);
      } else if (fileName == "stone.png") {
        assert(tileSpriteMap_.count(TileType::STONE) == 0);
        tileSpriteMap_[TileType::STONE] = std::move(texture);
      } else {
        throw std::runtime_error("Unexpected tile name" + fileName);
      }
    }
  }
}

sf::Texture& TileTextureProvider::getTileTexture(const TileType tileType) {
  if (tileSpriteMap_.count(tileType) == 0) {
    throw std::runtime_error("Invalid tile type. Not Found.");
  }

  return tileSpriteMap_.at(tileType);
}
