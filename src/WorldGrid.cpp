#include "WorldGrid.h"
#include <folly/Format.h>
#include <folly/Singleton.h>
#include <iostream>
#include <string>

namespace fgm {

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
}
