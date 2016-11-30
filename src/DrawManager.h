#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <mutex>

namespace fgm {
class DrawManager {
public:
  DrawManager() {}
  DrawManager(const DrawManager&) = delete;
  DrawManager& operator=(const DrawManager&) = delete;
  DrawManager(DrawManager&&) = default;
  DrawManager& operator=(DrawManager&&) = default;

  void draw(sf::RenderWindow& window);

  void add(std::shared_ptr<sf::Drawable> drawable);

private:
  std::vector<std::shared_ptr<sf::Drawable>> drawables_;
  std::mutex drawablesMutex_;
};
}
