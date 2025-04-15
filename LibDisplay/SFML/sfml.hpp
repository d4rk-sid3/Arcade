/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** sfml
*/

#ifndef SFML_HPP_
#define SFML_HPP_
#include "./../../IModuleDisplay.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../SDL/sdl.hpp"

class Sfml : public IModuleDisplay {
    public:
        ~Sfml();
        static Sfml* getInstance() {
            if (s_pInstance == nullptr) {
                s_pInstance = new Sfml();
            }
            return s_pInstance;
        }
        void init(std::vector <GameElement> configs) override;
        void handleInput() override;
        TrackPack getEvent() override;
        void draw() override;
        void update(std::vector <GameElement> configs) override;
        void stop() override;
        void destroy() override;
        void clean();
        void update_menu();
        void draw_menu();
        void handleInput(int value);
        TrackPack getKeyPressed() override {return keyPressed;};
        void init_menu();

    private:
        TrackPack keyPressed;
        sf::RenderWindow window;
        sf::Event event;
        std::vector<std::pair<sf::Sprite *, sf::Texture *>> images;
        std::vector <GameElement> oldState;
        static Sfml *s_pInstance;
        sf::Font *font = new sf::Font;
        Sfml();
};

#endif /* !SFML_HPP_ */