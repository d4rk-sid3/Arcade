/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** sfml
*/

#ifndef SFML_HPP_
#define SFML_HPP_
    #include <SFML/Graphics.hpp>
    #include <iostream>

    class sfml {
        private:
            sf::RenderWindow window;
            sf::Event event;
            sf::RectangleShape rect;

        public:
            sfml();
            void create_rect(sf::RectangleShape *rect);
            void keyinput();
            ~sfml();

    };

#endif /* !SFML_HPP_ */
