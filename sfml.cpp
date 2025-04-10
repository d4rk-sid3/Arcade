/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** Sfml
*/

#include "sfml.hpp"

Sfml::Sfml() : window(sf::VideoMode(800, 600), "Arcade", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close)
{
}

void Sfml::handleInput()
{
    stop();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        keyPressed =  UP;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        keyPressed =  DOWN;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        keyPressed =  LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        keyPressed =  RIGHT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        window.close();
    }
}

TrackPack Sfml::getEvent()
{
    return keyPressed;
}

void Sfml::init(std::vector <GameElement> configs)
{
    actualState = configs;
    for (int i = 0; i < configs.size(); i++) {
        int size = configs[i].getSpriteSize();
        int posX = configs[i].getPosX();
        int posY = configs[i].getPosY();
        sf::Texture texture;
        if (!texture.loadFromFile(configs[i].getSprite())) {
            std::cerr << "Error loading background image" << std::endl;
            std::exit(84);
        }
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(posX * size, posY * size));
        images.push_back(std::make_pair(sprite, texture));
    }
}

void Sfml::draw()
{
    handleInput();
    window.clear();  
    for (int i = 0; i < images.size(); i++)
        window.draw(images[i].first);  
    window.display();
}

void Sfml::update(std::vector <GameElement> configs)
{
    for (int a = 0; a < configs.size(); a++) {
        if (!(configs[a] == actualState[a])) {
            actualState[a] = configs[a];
            int size = actualState[a].getSpriteSize();
            int posX = actualState[a].getPosX();
            int posY = actualState[a].getPosY();
            sf::Texture texture;
            if (!texture.loadFromFile(actualState[a].getSprite())) {
                std::cerr << "Error loading background image" << std::endl;
                std::exit(84);
            }
            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setPosition(sf::Vector2f(posX * size, posY * size));
            images[a].first = sprite;
            images[a].second = texture;
        }
    }
}

Sfml::~Sfml()
{
}

void Sfml::stop()
{
    while (window.pollEvent(event)) {  
        if (event.type == sf::Event::Closed) {
            actualState.~vector();
            window.close();  
        }
    }
}