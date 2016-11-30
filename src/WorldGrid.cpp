#include "WorldGrid.h"

WorldGrid::WorldGrid(const size_t x,
                     const size_t y) { // Initialize to passed dimensions
  for (int i = 0; i < x; i++) {
    auto row = std::vector<WorldTile>();
    row.resize(y);
    grid_.push_back(std::move(row));
  }
}
