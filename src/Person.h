#pragma once

#include "AnimatedSprite.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <mutex>

namespace fgm {
struct Animations {
  Animation down;
  Animation up;
  Animation left;
  Animation right;
};
using stat_t = uint64_t;
static constexpr stat_t kStatMax = 100;

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

  void processEvent(sf::RenderWindow& window,
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

  // void draw(sf::RenderWindow& window) {
  //   std::lock_guard<std::mutex> lock(eventablesMutex_);
  //   for (const auto& eventable : eventables_) {
  //     window.draw(*eventable);
  //   }
  // }

  void add(std::shared_ptr<Eventable> eventable) {
    std::lock_guard<std::mutex> lock(eventablesMutex_);
    eventables_.push_back(eventable);
  }

private:
  std::vector<std::shared_ptr<Eventable>> eventables_;
  std::mutex eventablesMutex_;
};

class DrawManager {
public:
  DrawManager() {}
  DrawManager(const DrawManager&) = delete;
  DrawManager& operator=(const DrawManager&) = delete;
  DrawManager(DrawManager&&) = default;
  DrawManager& operator=(DrawManager&&) = default;

  void draw(sf::RenderWindow& window) {
    std::lock_guard<std::mutex> lock(drawablesMutex_);
    for (const auto& drawable : drawables_) {
      window.draw(*drawable);
    }
  }

  void add(std::shared_ptr<sf::Drawable> drawable) {
    std::lock_guard<std::mutex> lock(drawablesMutex_);
    drawables_.push_back(drawable);
  }

private:
  std::vector<std::shared_ptr<sf::Drawable>> drawables_;
  std::mutex drawablesMutex_;
};

class Updateable {
public:
  virtual void update() = 0;
};

class UpdateManager : public Updateable {
public:
  UpdateManager() {}
  UpdateManager(const UpdateManager&) = delete;
  UpdateManager& operator=(const UpdateManager&) = delete;
  UpdateManager(UpdateManager&&) = default;
  UpdateManager& operator=(UpdateManager&&) = default;

  void update() override;
  void add(std::shared_ptr<Updateable> up) {
    std::lock_guard<std::mutex> lock(updateablesMutex_);
    updateables_.push_back(up);
  }

private:
  std::vector<std::shared_ptr<Updateable>> updateables_;
  std::mutex updateablesMutex_;
};

class Person : public Updateable, public Eventable, public sf::Drawable {
public:
  Person();
  Person(const Person&) = delete;
  Person& operator=(const Person&) = delete;
  Person(Person&&) = default;
  Person& operator=(Person&&) = default;

  void update() override;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  void processEvent(const sf::Event& event, const sf::Time& frameTime) override;

private:
  stat_t health_ = kStatMax;
  stat_t hunger_ = 0;
  stat_t sleepiness_ = 0;
  float speed_ = 1.0;

  sf::Texture texture_;
  Animations animations_;
  Animation& curAnimation_;
  AnimatedSprite sprite_;
  sf::Vector2f movement_{0.f, 0.f};
};
}
