#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

int main() {
    const uint windowWidth = 800, windowHeight = 480;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Obliterate!");

    sf::Texture backgroundTexture, bossTexture, fireTexture;
    sf::Sprite backgroundSprite, bossSprite;

    sf::RectangleShape infoPanel(sf::Vector2f(120, 80));
    infoPanel.setPosition(0, 450);

    std::vector<sf::Sprite> fireVector;


    if (!backgroundTexture.loadFromFile("../resources/background.jpg")) {
        window.close();
    }

    if (!bossTexture.loadFromFile("../resources/boss/generic-lost-soul-150x160.png")) {
        window.close();
    }

    if (!fireTexture.loadFromFile("../resources/boss/fire-70x111.png")) {
        window.close();
    }

    backgroundSprite.setTexture(backgroundTexture);
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
            bossSprite.move(0.25, 0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            float newPosition = bossPosition.x - 0.25f;
            bossSprite.setPosition(newPosition, 0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            sf::Sprite fire;
            fire.setPosition(bossPosition.x, bossPosition.y);
            fire.setTexture(fireTexture);
            fireVector.push_back(fire);
        }

        //update all fires that has been shot
        for (auto &fire : fireVector) {
            fire.move(0, 0.25);

            //TODO remove unneeded fires

            window.draw(fire);
        }

        //window.draw(bossPositionText);
        window.draw(infoPanel);
        window.draw(bossSprite);
        window.display();
    }

    return 0;
}
