/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

    #include <SFML/Graphics.hpp>  
    #include <iostream>  
    #include <vector>  
    #include <ctime>  
    #include <cstdlib>  
    #include <thread>

    class nibbler_l {
        private:
            std::vector<std::string> map;
            std::vector<std::pair<int, int>> snake;
            char d;
            int x_food, y_food;
            int x, y;

        public:
            nibbler_l(int w, int h);
            ~nibbler_l();
            void direction(char newDirection);
            bool move();
            const std::vector<std::string>& getMap() const;
            void food(int count);
    };

    class nibbler_display {
        private:
            nibbler_l & logique;

        public:
            nibbler_display();
            ~nibbler_display();
            void draw();
            void key_input();
            void move_snake(sf::Clock *clock);   
    };

#endif /* !NIBBLER_HPP_ */
