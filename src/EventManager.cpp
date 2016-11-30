#include "EventManager.h"

namespace fgm {

void EventManager::processEvent(sf::RenderWindow& window,
                                const sf::Event& event,
                                const sf::Time& frameTime) {
  std::lock_guard<std::mutex> lock(eventablesMutex_);
  if (event.type == sf::Event::Closed) {
    window.close();
    return;
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
