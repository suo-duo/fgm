#include "EventManager.h"

namespace fgm {

void EventManager::processEvent(sf::RenderWindow& window) {
  std::lock_guard<std::mutex> lock(eventablesMutex_);

  sf::Time frameTime = clock_.restart();
  sf::Event event;

  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
      return;
    }
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape) {
      window.close();
      return;
    }
  }

  for (auto& eventable : eventables_) {
    eventable->processEvent(event, frameTime);
  }
}

void EventManager::add(std::shared_ptr<Eventable> eventable) {
  std::lock_guard<std::mutex> lock(eventablesMutex_);
  eventables_.push_back(eventable);
}
}
