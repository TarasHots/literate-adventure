#include <iostream>
#include <string>
#include <forward_list>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

using namespace std;

bool is_fire_away(const sf::Sprite &fire) { return fire.getPosition().y >= 480; };

int main() {
    const uint windowWidth = 800, windowHeight = 480;
    const float fireDelaySec = 1.0;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Obliterate!");

    sf::Texture backgroundTexture, bossTexture, fireTexture;
    sf::Sprite backgroundSprite, bossSprite;
    sf::SoundBuffer bossShotBuffer, bossBreathBuffer;

    sf::RectangleShape infoPanel(sf::Vector2f(120, 80));
    infoPanel.setPosition(0, 450);

    std::forward_list<sf::Sprite> fires;

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

    if (!bossShotBuffer.loadFromFile("../resources/boss/sound/fireball.wav"))
    {
        window.close();
    }

    if (!bossBreathBuffer.loadFromFile("../resources/boss/sound/breath.wav"))
    {
        window.close();
    }

    sf::Sound bossFireballSound, bossBreathSound;
    bossFireballSound.setBuffer(bossShotBuffer);
    bossBreathSound.setBuffer(bossBreathBuffer);

    bossBreathSound.play();

    sf::Clock clock;
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

            sf::Time started = clock.restart();

            //shoot not to often
            if (started.asSeconds() >= fireDelaySec) {
                sf::Sprite fire;
                //align shooting position
                float fireXPosition = bossPosition.x + 35;
                float fireYPosition = bossPosition.y + 30;

                fire.setPosition(fireXPosition, fireYPosition);
                fire.setTexture(fireTexture);
                fires.push_front(fire);
                bossFireballSound.play();
            }
        }

        fires.remove_if(is_fire_away);

        //update all fires that has been shot
        for (auto &fire : fires) {
            fire.move(0, 0.25);

            window.draw(fire);
        }

        window.draw(infoPanel);
        window.draw(bossSprite);
        window.display();
    }

    return 0;
}
