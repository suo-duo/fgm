#include "WorldGrid.h"
#include <folly/Format.h>
#include <folly/Singleton.h>

namespace {

static const std::string tilePath = "./assets/img/tiles/";
folly::Singleton<TileTextureProvider> tileTextureProvider([]() {
  return new TileTextureProvider();
});
}

WorldTile::WorldTile(const grid_t x,
                     const grid_t y,
                     const TileType type,
                     size_t pixelsPerTileEdge)
    : x_(x), y_(y), type_(type) {
  const auto& texture =
      folly::Singleton<TileTextureProvider>::try_get_fast()->getTileTexture(
          type);

  sprite_.setTexture(texture);
  sprite_.setPosition(x * pixelsPerTileEdge, y * pixelsPerTileEdge);
}

WorldGrid::WorldGrid(const size_t widthInPixels,
                     const size_t heightInPixels,
                     const size_t pixelsPerTileEdge)
    : pixelsPerTileEdge_(pixelsPerTileEdge) {

  if (widthInPixels == 0 || heightInPixels == 0) {
    throw std::runtime_error(
        folly::format(
            "Invalid grid dimensions. widthInPixels: {}, heightInPixels: {}",
            widthInPixels,
            heightInPixels)
            .str());
  }

  // Initialize to passed dimensions
  grid_t widthInTiles = widthInPixels / pixelsPerTileEdge_;
  grid_t heightInTiles = heightInPixels / pixelsPerTileEdge_;
  for (int y = 0; y < heightInTiles; y++) {
    std::vector<WorldTile> row;
    for (int x = 0; x < widthInTiles; x++) {
      row.emplace_back(x, y, TileType::LAVA, pixelsPerTileEdge_);
    }
    grid_.push_back(std::move(row));
  }
}

WorldTile& WorldGrid::get(const grid_t x, const grid_t y) {
  if (x >= width() || y >= height()) {
    throw std::runtime_error(
        folly::format("Invalid coordinate request: x: {}, y: {}", x, y).str());
  }

  return grid_.at(y).at(x);
}

TileTextureProvider::TileTextureProvider() {
  // Get the path to the tile images on disk
  const auto path = boost::filesystem::path(tilePath);
  auto dirIter = boost::filesystem::directory_iterator(path);
  for (const auto dirEntry : dirIter) {
    const auto path = dirEntry.path();
    if (boost::filesystem::is_regular_file(path)) {
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
