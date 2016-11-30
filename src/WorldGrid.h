#pragma once

#include <SFML/Graphics.hpp>
#include <boost/filesystem.hpp>
#include <cstddef>
#include <unordered_map>
#include <utility>
#include <vector>

static const std::string tilePath = "./assets/img/tiles/";

using grid_t = uint32_t;

enum class TileType { LAVA, GRASS };

class TileSpriteProvider {
public:
  TileSpriteProvider() {
    const auto path = boost::filesystem::path(tilePath);
    auto dirIter = boost::filesystem::directory_iterator(path);
    for (const auto dirEntry : dirIter) {
      const auto path = dirEntry.path();
      if (boost::filesystem::is_regular_file(path)) {
        sf::Texture texture;
        if (!texture.loadFromFile(path.string())) {
          throw std::runtime_error("Failed to load texture from path: " +
                                   path.string());
        }

        sf::Sprite sprite;
        sprite.setTexture(texture);

        TileType tileType;
        const auto fileName = path.filename().string();
        if (fileName == "lava.png") {
          assert(tileSpriteMap_.count(TileType::LAVA) == 0);
          tileSpriteMap_[TileType::LAVA] = sprite;
        } else {
          //
        }
      }
    }

    // sf::Texture playerTexture;
    // if (!playerTexture.loadFromFile("./assets/img/player.png")) {
    // }
  }

private:
  std::unordered_map<TileType, sf::Sprite> tileSpriteMap_;
};

struct WorldTile {
  grid_t x;
  grid_t y;
};

class WorldGrid {
  WorldGrid(size_t x, size_t y);

  WorldTile& get(size_t x, size_t y);

private:
  std::vector<std::vector<WorldTile>> grid_;
};
