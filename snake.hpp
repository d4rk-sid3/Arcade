/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

    #include <SFML/Graphics.hpp>  
    #include <iostream>
    #include <fstream>
    #include <vector>  
    #include <ctime>  
    #include <cstdlib>
    #include <sstream>
    #include <thread>

    class snake_l {
        private:
            std::vector<std::string> map;
            std::vector<std::pair<int, int>> snake;
            char d;
            int x_food, y_food;
            int x, y;

        public:
            snake_l(int w, int h, const std::string& m);
            ~snake_l();
            void eatfood();
            void direction(char newDirection);
            bool move();
            const std::vector<std::string>& getMap() const;

    };

    class snake_display {   
        private:
            snake_l &logic;
            sf::RenderWindow window;
            sf::Event event;
            sf::Texture head_texture;
            sf::Texture blob_texture;
            sf::Texture wall_texture;
            sf::Texture death_texture;
            sf::Texture apple_texture;
            sf::Sprite head_sprite;
            sf::Sprite blob_sprite;
            sf::Sprite wall_sprite;
            sf::Sprite death_sprite;
            sf::Sprite apple_sprite;


        public:
            snake_display(snake_l &l);
            void draw();
            ~snake_display();
            void key_input();
            void move_snake(sf::Clock *clock);
            void create_head();
            void create_blob();
            void create_wall();
            void create_death();
            void create_apple();

    };

#endif /* !SNAKE_HPP_ */
