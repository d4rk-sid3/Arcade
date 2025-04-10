/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** Sfml
*/

#include "sfml.hpp"

Sfml::Sfml()
{
}

Sfml::~Sfml()
{
}

void Sfml::init(std::vector <GameElement> configs)
{

}

TrackPack Sfml::getEvent()
{
    return keyPressed;
}

void Sfml::draw()
{

}

void Sfml::update()
{

}

void Sfml::stop()
{

}

void nibbler_display::create_head()
{
    if (!head_texture.loadFromFile("head.png")) {
        std::cerr << "Error loading background image" << std::endl;
        return;
    }

    float scale = 20.0f / 1024.0f;
    head_sprite.setTexture(head_texture);
    head_sprite.setScale(scale, scale);
}

void nibbler_display::create_blob()
{
    if (!blob_texture.loadFromFile("blob.png")) {
        std::cerr << "Error loading background image" << std::endl;
        return;
    }

    float scale = 20.0f / 512.0f;
    blob_sprite.setTexture(blob_texture);
    blob_sprite.setScale(scale, scale);
}

void nibbler_display::create_wall()
{
    if (!wall_texture.loadFromFile("wall.png")) {
        std::cerr << "Error loading background image" << std::endl;
        return;
    }

    float scale = 20.0f / 216.0f;
    wall_sprite.setTexture(wall_texture);
    wall_sprite.setScale(scale, scale);
}

void nibbler_display::create_death()
{
    if (!death_texture.loadFromFile("xx.png")) {
        std::cerr << "Error loading background image" << std::endl;
        return;
    }

    float scale = 20.0f / 1024.0f;
    death_sprite.setTexture(death_texture);
    death_sprite.setScale(scale, scale);
}

void nibbler_display::create_apple()
{
    if (!apple_texture.loadFromFile("apple.png")) {
        std::cerr << "Error loading background image" << std::endl;
        return;
    }

    float scale = 20.0f / 1024.0f;
    apple_sprite.setTexture(apple_texture);
    apple_sprite.setScale(scale, scale);
}

nibbler_display::nibbler_display(nibbler_l &l): logic(l), window(sf::VideoMode(963, 600), "nibbler Game")
{
    create_head();
    create_blob();
    create_wall();
    create_death();
    create_apple();
}

void Sfml::init(std::vector <GameElement> configs)
{
    for (int i = 0; i < configs.size(); i++) {
        
    }
}

void Sfml::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        direction =  UP;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        direction =  DOWN;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction =  LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction =  RIGHT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        window.close();
    }
}

void nibbler_display::move_nibbler(sf::Clock *clock)
{
    if ((*clock).getElapsedTime().asMilliseconds() >= 150) {  
        if (!logic.move()) {  
            std::cout << "Game Over!" << std::endl;  
            window.close();  
        }  
        (*clock).restart();
    }
}

void nibbler_display::draw()
{
    window.setFramerateLimit(10);  
    const auto& map = logic.getMap();  
    int cellSize = 20; 
    sf::Clock clock;
    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));

    while (window.isOpen()) {  
        sf::Event event;  
        while (window.pollEvent(event)) {  
            if (event.type == sf::Event::Closed) {  
                window.close();  
            }
        }
        key_input();
        move_nibbler(&clock);
         
        window.clear();  
        for (size_t y = 0; y < map.size(); ++y) {  
            for (size_t x = 0; x < map[y].size(); ++x) {  

                if (map[y][x] == 'O') {
                    head_sprite.setPosition(x * cellSize, y * cellSize);
                    window.draw(head_sprite); 
                } else if (map[y][x] == 'X') {  
                    apple_sprite.setPosition(x * cellSize, y * cellSize);
                    window.draw(apple_sprite);
                } else if (map[y][x] == '#'){  
                    wall_sprite.setPosition(x * cellSize, y * cellSize);
                    window.draw(wall_sprite);
                } else if (map[y][x] == 'B') {
                    blob_sprite.setPosition(x * cellSize, y * cellSize);
                    window.draw(blob_sprite);
                } else {
                    cell.setPosition(x * cellSize, y * cellSize);
                    cell.setFillColor(sf::Color::Black);
                    window.draw(cell);
                }
            }  
        }  
        window.display();
    }  
}

nibbler_display::~nibbler_display()
{

}
