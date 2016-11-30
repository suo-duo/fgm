#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <mutex>

namespace fgm {
// Extend sf::Drawable so we can require our renderable objects have other
// properties
class Renderable : public sf::Drawable {};

class RenderManager {
public:
  RenderManager() {}
  RenderManager(const RenderManager&) = delete;
  RenderManager& operator=(const RenderManager&) = delete;
  RenderManager(RenderManager&&) = default;
  RenderManager& operator=(RenderManager&&) = default;

  void render(sf::RenderWindow& window);

  void add(std::shared_ptr<Renderable> renderable);

private:
  std::vector<std::shared_ptr<Renderable>> renderables_;
  std::mutex renderablesMutex_;
};
}
