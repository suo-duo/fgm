#include "AnimatedSprite.h"
#include "Person.h"
#include "WorldGrid.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace fgm;

int main() {
  // setup window
  size_t xPixels = 800;
  size_t yPixels = 600;
  sf::Vector2i screenDimensions(xPixels, yPixels);
  sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y),
                          "Animations!");
  window.setFramerateLimit(60);

  const auto pixelsPerTileEdge = 50;
  const auto worldGrid = WorldGrid(xPixels, yPixels, pixelsPerTileEdge);


  sf::Texture caravanTexture;
  if (!caravanTexture.loadFromFile("./assets/img/caravan.png")) {
    std::cout << "Failed to load caravan spritesheet!" << std::endl;
    return 1;
  }

  sf::Clock frameClock;
  sf::Clock updateClock;

  float speed = 80.f;
  bool noKeyWasPressed = true;


  auto person = std::make_shared<Person>();

  UpdateManager registry;
  registry.add(person);

  EventManager eventManager;
  eventManager.add(person);

  DrawManager drawManager;
  drawManager.add(person);

  while (window.isOpen()) {
    sf::Time frameTime = frameClock.restart();

    sf::Event event;
    while (window.pollEvent(event)) {
      eventManager.processEvent(window, event, frameTime);
    }

    // draw
    window.clear();

    const bool shouldUpdate =
        updateClock.getElapsedTime() > sf::milliseconds(100);
    if (shouldUpdate) {
      registry.update();
      updateClock.restart();
    }

    window.draw(worldGrid);
    drawManager.draw(window);

    window.display();
  }

  return 0;
}
