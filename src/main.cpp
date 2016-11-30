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
  const auto worldGrid =
      std::make_shared<WorldGrid>(xPixels, yPixels, pixelsPerTileEdge);

  sf::Texture caravanTexture;
  if (!caravanTexture.loadFromFile("./assets/img/caravan.png")) {
    std::cout << "Failed to load caravan spritesheet!" << std::endl;
    return 1;
  }

  auto person = std::make_shared<Person>();

  UpdateManager updateManager;
  updateManager.add(person);

  EventManager eventManager;
  eventManager.add(person);

  RenderManager renderManager;
  renderManager.add(worldGrid);
  renderManager.add(person);

  while (window.isOpen()) {
    eventManager.processEvent(window);
    updateManager.update();
    renderManager.render(window);
  }

  return 0;
}
