/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** Sfml
*/

#include "sfml.hpp"

Sfml* Sfml::s_pInstance = 0;

Sfml::Sfml()
{
}

void Sfml::handleInput()
{
    keyPressed = NONE;
    stop();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        keyPressed =  UP;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        keyPressed =  DOWN;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        keyPressed =  LEFT;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        keyPressed =  RIGHT;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        keyPressed = QUIT;
        window.close();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
        keyPressed = LIB_LEFT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        keyPressed = LIB_RIGHT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
        keyPressed = MENU;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
        keyPressed = GAME_LEFT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        keyPressed = GAME_RIGHT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
        keyPressed = RESTART;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        keyPressed = PAUSE;
    } else {
        keyPressed = NONE;
    }
}

TrackPack Sfml::getEvent()
{
    return keyPressed;
}

void Sfml::init(std::vector <GameElement> configs)
{
    window.create(sf::VideoMode(1920, 1080), "Arcade", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
    keyPressed = NONE;
    oldState.clear();
    for (int a = 0; a < configs.size(); a++) {
        oldState.push_back(configs[a]);
    }
    images.clear();
    for (int i = 0; i < configs.size(); i++) {
        sf::Texture *texture = new sf::Texture;
        sf::Sprite *sprite = new sf::Sprite;
        int size = configs[i].getSpriteSize();
        int posX = configs[i].getPosX();
        int posY = configs[i].getPosY();
        if (!texture->loadFromFile(configs[i].getSprite())) {
            std::cerr << "Error loading background image" << std::endl;
            std::exit(84);
        }
        sprite->setTexture(*texture);
        sprite->setPosition(sf::Vector2f(posX * size, posY * size));
        images.push_back(std::make_pair(sprite, texture));
    }
}

void Sfml::draw()
{
    handleInput();
    window.clear();
    for (int i = 0; i < images.size(); i++)
        window.draw(*images[i].first);  
    window.display();
}

void Sfml::update(std::vector<GameElement> configs)
{
    for (int a = 0; a < configs.size(); a++) {
        if (!(configs[a] == oldState[a])) {
            oldState[a] = configs[a];
            oldState[a].setPosX(configs[a].getPosX());
            oldState[a].setPosY(configs[a].getPosY());
            oldState[a].setSymbol(configs[a].getSymbol());
            oldState[a].setSpriteSize(configs[a].getSpriteSize());
            oldState[a].setSprite(configs[a].getSprite());
            int size = oldState[a].getSpriteSize();
            int posX = oldState[a].getPosX();
            int posY = oldState[a].getPosY();
            images[a].second->loadFromFile(oldState[a].getSprite());
            images[a].first->setTexture(*(images[a].second));
            images[a].first->setPosition(sf::Vector2f(posX * size, posY * size));
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
            keyPressed = QUIT;
        }
    }
}

void Sfml::destroy()
{
    oldState.clear();
    window.close();
    for (int i = 0; i < images.size(); i++) {
        delete images[i].first;
        delete images[i].second;
    }
    images.clear();
}

extern "C" IModuleDisplay* createInstance() {
    return new Sfml();
}

extern "C" void destroyInstance(IModuleDisplay *instance) {
    delete instance;
}