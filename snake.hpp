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
    #include <vector>  
    #include <ctime>  
    #include <cstdlib>  
    #include <thread>

    class snake_l {
        private:
            std::vector<std::string> map;
            std::vector<std::pair<int, int>> snake;
            char d;
            int x_food, y_food;
            int x, y;

        public:
            snake_l(int w, int h);
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

        public:
            snake_display(snake_l &l);
            void draw();
            ~snake_display();
            void key_input();
            void move_snake(sf::Clock *clock);
    };

#endif /* !SNAKE_HPP_ */
