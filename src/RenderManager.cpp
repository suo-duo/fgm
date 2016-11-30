#include "RenderManager.h"

namespace fgm {
void RenderManager::render(sf::RenderWindow &window) {
  std::lock_guard<std::mutex> lock(renderablesMutex_);

  window.clear();
  for (const auto& renderable : renderables_) {
    window.draw(*renderable);
  }
  window.display();
}

void RenderManager::add(std::shared_ptr<Renderable> renderable) {
  std::lock_guard<std::mutex> lock(renderablesMutex_);
  renderables_.push_back(renderable);
}
}
