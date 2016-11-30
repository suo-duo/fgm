#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <mutex>

namespace fgm {

class Eventable {
public:
  virtual void processEvent(const sf::Event& event,
                            const sf::Time& frameTime) = 0;
};

class EventManager {
public:
  EventManager() {}
  EventManager(const EventManager&) = delete;
  EventManager& operator=(const EventManager&) = delete;
  EventManager(EventManager&&) = default;
  EventManager& operator=(EventManager&&) = default;

  void processEvent(sf::RenderWindow& window);

  void add(std::shared_ptr<Eventable> eventable);

private:
  std::vector<std::shared_ptr<Eventable>> eventables_;
  std::mutex eventablesMutex_;
  sf::Clock clock_;
};
}
