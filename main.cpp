#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include <iostream>

int main()
{
    // setup window
    sf::Vector2i screenDimensions(800,600);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Animations!");
    window.setFramerateLimit(60);

    // load texture (spritesheet)
    sf::Texture texture;
    if (!texture.loadFromFile("./player.png"))
    {
        std::cout << "Failed to load player spritesheet!" << std::endl;
        return 1;
    }

    // set up the animations for all four directions (set spritesheet and push frames)
    Animation walkingAnimationDown;
    walkingAnimationDown.setSpriteSheet(texture);
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

    Animation walkingAnimationLeft;
    walkingAnimationLeft.setSpriteSheet(texture);
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect( 0, 32, 32, 32));

    Animation walkingAnimationRight;
    walkingAnimationRight.setSpriteSheet(texture);
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect( 0, 64, 32, 32));

    Animation walkingAnimationUp;
    walkingAnimationUp.setSpriteSheet(texture);
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect( 0, 96, 32, 32));

    Animation* currentAnimation = &walkingAnimationDown;

    // set up AnimatedSprite
    AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
    animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));

    sf::Clock frameClock;

    float speed = 80.f;
    bool noKeyWasPressed = true;

    while (window.isOpen())
    {
        sf::Time frameTime = frameClock.restart();
        sf::Vector2f movement(0.f, 0.f);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                noKeyWasPressed = false;
                switch(event.key.code) {
                    case sf::Keyboard::Up:
                        currentAnimation = &walkingAnimationUp;
                        movement.y -= speed;
                        break;
                    case sf::Keyboard::Down:
                        currentAnimation = &walkingAnimationDown;
                        movement.y += speed;
                        break;
                    case sf::Keyboard::Left:
                        currentAnimation = &walkingAnimationLeft;
                        movement.x -= speed;
                        break;
                    case sf::Keyboard::Right:
                        currentAnimation = &walkingAnimationRight;
                        movement.x += speed;
                        break;
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    default:
                        break;
                }
            }
        }

        animatedSprite.play(*currentAnimation);
        animatedSprite.move(movement * frameTime.asSeconds());

        // if no key was pressed stop the animation
        if (noKeyWasPressed)
        {
            animatedSprite.stop();
        }
        noKeyWasPressed = true;

        // update AnimatedSprite
        animatedSprite.update(frameTime);

        // draw
        window.clear();
        window.draw(animatedSprite);
        window.display();
    }

    return 0;
}