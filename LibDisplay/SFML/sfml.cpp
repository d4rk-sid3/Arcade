/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** Sfml
*/

#include "sfml.hpp"
#include <set>

Sfml* Sfml::s_pInstance = 0;

Sfml::Sfml()
{
}

void Sfml::init_menu()
{
    window.create(sf::VideoMode(1920, 1080), "Arcade", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
    keyPressed = NONE;
    TextureManager::Instance()->load("assets/background.jpeg", "background", &window);
    TextureManager::Instance()->load("assets/borne.png", "borne", &window);
    TextureManager::Instance()->load("assets/player.png", "player", &window);
    TextureManager::Instance()->load("assets/Untitled1.png", "message", &window);
    if (!font->loadFromFile("assets/ROMANS.ttf")) {
        std::cerr << "LOL" << std::endl;
    };
    return;
}

void Sfml::update_menu()
{
    if (Menu::Instance()->isFinished()) {
        keyPressed = QUIT;
        return;
    }
    if (Player::Instance()->getFocus() == Focus::MENU) {
        Menu::Instance()->update(1);
        return;
    }
    if (Player::Instance()->getFocus() == Focus::PLAYER) {
        Player::Instance()->update(1);
        return;
    }
    Player::Instance()->update_name(1);
    Player::Instance()->adjust_letters_position();   
}

void Sfml::draw_menu()
{
    window.clear();
    if (Player::Instance()->getFocus() == Focus::MENU) {
        Menu::Instance()->render(&window, font);
        window.display(); // draw to the screen
        return;
    }
    if (Player::Instance()->getFocus() == Focus::PLAYER) {
        TextureManager::Instance()->draw("background", 0, 0, 1920, 1080, &window);
        TextureManager::Instance()->draw("borne", 300, 80, 500, 500, &window);
        Player::Instance()->draw(&window, font);
        if (Player::Instance()->getBool())
            TextureManager::Instance()->draw("message", 748, 10, 594, 533, &window);
        window.setFramerateLimit(10);
        window.display(); // draw to the screen
        return;
    }
    Player::Instance()->display_letters(&window, font);
    Player::Instance()->adjust_letters_position();
    window.display(); // draw to the screen
    return;
}

void Sfml::handleInput(int value)
{
    keyPressed = NONE;
    stop();

    const TrackPack tabs[27] = {TrackPack::A, TrackPack::B, TrackPack::C, TrackPack::D,
        TrackPack::E, TrackPack::F, TrackPack::G, TrackPack::H,
        TrackPack::I, TrackPack::J, TrackPack::K, TrackPack::L,
        TrackPack::M, TrackPack::N, TrackPack::O, TrackPack::P,
        TrackPack::Q, TrackPack::R, TrackPack::S, TrackPack::T,
        TrackPack::U, TrackPack::V, TrackPack::W, TrackPack::X,
        TrackPack::Y, TrackPack::Z, TrackPack::BACKSPACE
    };
    std::vector<sf::Keyboard::Key> tab = {sf::Keyboard::A, sf::Keyboard::B, sf::Keyboard::C, sf::Keyboard::D,
        sf::Keyboard::E, sf::Keyboard::F, sf::Keyboard::G, sf::Keyboard::H,
        sf::Keyboard::I, sf::Keyboard::J, sf::Keyboard::K, sf::Keyboard::L,
        sf::Keyboard::M, sf::Keyboard::N, sf::Keyboard::O, sf::Keyboard::P,
        sf::Keyboard::Q, sf::Keyboard::R, sf::Keyboard::S, sf::Keyboard::T,
        sf::Keyboard::U, sf::Keyboard::V, sf::Keyboard::W, sf::Keyboard::X,
        sf::Keyboard::Y, sf::Keyboard::Z, sf::Keyboard::BackSpace
    };
    if (event.type == sf::Event::KeyReleased) {
        for (int i = 0; i < 26; i++) {
            if (event.key.code == tab[i]) {
                keyPressed = tabs[i];
                return;
            }
        }
    }
    if (event.key.code == sf::Keyboard::Return)
        keyPressed = ENTER;
    return;
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

void Sfml::clean()
{
    window.close();
    return;
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
    return Sfml::getInstance();
}

extern "C" void destroyInstance(IModuleDisplay *instance) {
    //delete instance;
}