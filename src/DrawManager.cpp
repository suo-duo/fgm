#include "DrawManager.h"

namespace fgm {
void DrawManager::draw(sf::RenderWindow& window) {
  std::lock_guard<std::mutex> lock(drawablesMutex_);

  window.clear();
  for (const auto& drawable : drawables_) {
    window.draw(*drawable);
  }
  window.display();
}

void DrawManager::add(std::shared_ptr<sf::Drawable> drawable) {
  std::lock_guard<std::mutex> lock(drawablesMutex_);
  drawables_.push_back(drawable);
}
}
