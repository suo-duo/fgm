#pragma once

#include "AnimatedSprite.h"
#include "DrawManager.h"
#include "EventManager.h"
#include "UpdateManager.h"
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
  // TODO: everyone is named Bernard for now. Would be neat to have name generator.
  std::string name_ = "Bernard";
  stat_t health_ = kStatMax;
  stat_t hunger_ = 0;
  stat_t sleepiness_ = 0;
  float speed_ = 80.0;

  sf::Texture texture_;
  Animations animations_;
  Animation curAnimation_;
  AnimatedSprite sprite_;
};
}
