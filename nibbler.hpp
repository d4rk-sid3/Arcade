/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** nibbler
*/

#ifndef nibbler_HPP_
#define nibbler_HPP_

    #include <SFML/Graphics.hpp>  
    #include <iostream>
    #include <fstream>
    #include <vector>  
    #include <ctime>  
    #include <cstdlib>
    #include <sstream>
    #include <thread>

    class nibbler_l {
        private:
            std::vector<std::string> map;
            std::vector<std::pair<int, int>> nibbler;
            char d;
            int x_food, y_food;
            int x, y;
            int nb_fruit;
            int score;
            std::vector <std::pair<int, int>> foods;


        public:
            nibbler_l(int w, int h, const std::string& m);
            ~nibbler_l();
            void eatfood();
            void direction(char newDirection);
            bool move();
            bool new_direction(int new_x, int new_y);
            const std::vector<std::string>& getMap() const;

    };

    class nibbler_display {   
        private:
            nibbler_l &logic;
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
            nibbler_display(nibbler_l &l);
            void draw();
            ~nibbler_display();
            void key_input();
            void move_nibbler(sf::Clock *clock);
            void create_head();
            void create_blob();
            void create_wall();
            void create_death();
            void create_apple();

    };

#endif /* !nibbler_HPP_ */
