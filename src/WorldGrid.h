#pragma once

#include "TileTextureProvider.h"
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <utility>
#include <vector>

namespace fgm {

using grid_t = uint32_t;

class WorldTile : public sf::Drawable {
public:
  WorldTile(grid_t x, grid_t y, TileType type, size_t pixelsPerTileEdge);

  WorldTile(const WorldTile&) = delete;
  WorldTile& operator=(const WorldTile&) = delete;
  WorldTile(WorldTile&&) = default;
  WorldTile& operator=(WorldTile&&) = default;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    target.draw(sprite_, states);
  }

private:
  grid_t x_;
  grid_t y_;
  TileType type_;
  sf::Sprite sprite_;
};

/**
 * Core abstraction for the world grid. Stores tiles.
 *
 * Dimsions are X and Y. Origin is top left, going down is positive Y, going
 * right is positive X.
 */
class WorldGrid : public sf::Drawable {
public:
  // TODO delete copy constructor
  WorldGrid(size_t widthInPixels,
            size_t heightInPixels,
            size_t pixelsPerTileEdge);

  WorldGrid(const WorldGrid&) = delete;
  WorldGrid& operator=(const WorldGrid&) = delete;
  WorldGrid(WorldGrid&&) = default;
  WorldGrid& operator=(WorldGrid&&) = default;

  WorldTile& get(grid_t x, grid_t y);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    for (auto& row : grid_) {
      for (auto& tile : row) {
        tile.draw(target, states);
      }
    }
  }

  grid_t height() { return grid_.size(); }
  grid_t width() { return grid_.at(0).size(); };

private:
  // Height (y) is the outer vector
  // Width (x) is the inner vector
  std::vector<std::vector<WorldTile>> grid_;

  // Pixel per tile edge
  size_t pixelsPerTileEdge_;
};
}
