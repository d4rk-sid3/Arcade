/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** sfml
*/

#include "sfml.hpp"

sfml::sfml(): window(sf::VideoMode(500, 1000), "Arcade"), rect(sf::Vector2f(10, 20))
{
    create_rect(&rect);
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        keyinput();
        window.clear(sf::Color::Black);
        window.draw(rect);
        window.display();
    }
}

void sfml::create_rect(sf::RectangleShape *rect)
{
    (*rect).setFillColor(sf::Color::White);
    (*rect).setSize(sf::Vector2f(50, 50));
    (*rect).setPosition(10, 0);
}

void sfml::keyinput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        rect.move(-0.5, 0);
        rect.setFillColor(sf::Color::Red);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        rect.move(0.5, 0);
        rect.setFillColor(sf::Color::Blue);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        rect.move(0, -0.5);
        rect.setFillColor(sf::Color::Green);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        rect.move(0, 0.5);
        rect.setFillColor(sf::Color::Yellow);
    }
}

sfml::~sfml()
{

}

int main()
{
    sfml();
}
