#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape circleShape(100.f);
    circleShape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(circleShape);
        window.display();
    }

    return 0;
}