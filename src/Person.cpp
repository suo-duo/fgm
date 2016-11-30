#include "Person.h"
#include <iostream>

namespace fgm {
namespace {

sf::Texture prepTexture() {
  sf::Texture playerTexture;
  if (!playerTexture.loadFromFile("./assets/img/player.png")) {
    throw std::runtime_error("Could not load player image asset");
  }

  return playerTexture;
}

Animations prepAnimations(const sf::Texture& playerTexture) {
  // set up the animations for all four directions (set spritesheet and push
  // frames)
  Animations animations;

  animations.down.setSpriteSheet(playerTexture);
  animations.down.addFrame(sf::IntRect(32, 0, 32, 32));
  animations.down.addFrame(sf::IntRect(64, 0, 32, 32));
  animations.down.addFrame(sf::IntRect(32, 0, 32, 32));
  animations.down.addFrame(sf::IntRect(0, 0, 32, 32));

  animations.left.setSpriteSheet(playerTexture);
  animations.left.addFrame(sf::IntRect(32, 32, 32, 32));
  animations.left.addFrame(sf::IntRect(64, 32, 32, 32));
  animations.left.addFrame(sf::IntRect(32, 32, 32, 32));
  animations.left.addFrame(sf::IntRect(0, 32, 32, 32));

  animations.right.setSpriteSheet(playerTexture);
  animations.right.addFrame(sf::IntRect(32, 64, 32, 32));
  animations.right.addFrame(sf::IntRect(64, 64, 32, 32));
  animations.right.addFrame(sf::IntRect(32, 64, 32, 32));
  animations.right.addFrame(sf::IntRect(0, 64, 32, 32));

  animations.up.setSpriteSheet(playerTexture);
  animations.up.addFrame(sf::IntRect(32, 96, 32, 32));
  animations.up.addFrame(sf::IntRect(64, 96, 32, 32));
  animations.up.addFrame(sf::IntRect(32, 96, 32, 32));
  animations.up.addFrame(sf::IntRect(0, 96, 32, 32));

  return animations;
}
} // anonymous

Person::Person()
    : texture_(prepTexture()), animations_(prepAnimations(texture_)),
      curAnimation_(animations_.down) {
  size_t xPixels = 800;
  size_t yPixels = 600;
  sf::Vector2i screenDimensions(xPixels, yPixels);

  sprite_ = AnimatedSprite(sf::seconds(0.2), true, false);
  sprite_.setPosition(sf::Vector2f(screenDimensions / 2));
}

void Person::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(sprite_, states);
}

void Person::processEvent(const sf::Event& event, const sf::Time& frameTime) {
  bool noKeyWasPressed = true;
  sf::Vector2f movement(0.f, 0.f);

  if (event.type == sf::Event::KeyPressed) {
    noKeyWasPressed = false;
    switch (event.key.code) {
    case sf::Keyboard::Up:
      curAnimation_ = animations_.up;
      movement.y -= speed_;
      break;
    case sf::Keyboard::Down:
      curAnimation_ = animations_.down;
      movement.y += speed_;
      break;
    case sf::Keyboard::Left:
      curAnimation_ = animations_.left;
      movement.x -= speed_;
      break;
    case sf::Keyboard::Right:
      curAnimation_ = animations_.right;
      movement.x += speed_;
      break;
    default:
      noKeyWasPressed = true;
      break;
    }
  }

  sprite_.play(curAnimation_);
  sprite_.move(movement * frameTime.asSeconds());

  if (noKeyWasPressed) {
    sprite_.stop();
  }

  sprite_.update(frameTime);
}

void Person::update() {
  hunger_++;
  sleepiness_++;

  if (hunger_ > kStatMax) {
    health_--;
  }
  if (sleepiness_ > kStatMax) {
    health_--;
  }
  std::cout << "Health: " << health_ << std::endl;
  std::cout << "Hunger: " << hunger_ << std::endl;
  std::cout << "Sleepiness: " << sleepiness_ << std::endl;
  std::cout << std::endl;
}
}
