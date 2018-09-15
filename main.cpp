#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

int main() {
    const uint windowWidth = 800, height = 480;

    sf::RenderWindow window(sf::VideoMode(windowWidth, height), "Obliterate!");

    sf::Texture background, bossTexture;
    if (!background.loadFromFile("../resources/background.jpg")) {
        window.close();
    }

    sf::Sprite backgroundSprite, bossSprite;
    backgroundSprite.setTexture(background);

    if (!bossTexture.loadFromFile("../resources/boss/generic-lost-soul-150x160.png")) {
        window.close();
    }

    bossSprite.setTexture(bossTexture);


    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(backgroundSprite);

        sf::Vector2f bossPosition = bossSprite.getPosition();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            // left key is pressed: move our character
            float newX = bossPosition.x;
            newX++;

            if (newX >= windowWidth) {
                break;
            }

            bossSprite.move(sf::Vector2f(0.25, 0));//move(newX, bossPosition.y);
        }


        window.draw(bossSprite);
        window.display();
    }

    return 0;
}
