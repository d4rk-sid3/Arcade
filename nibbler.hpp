/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** nibbler
*/

#ifndef Nibbler_HPP_
#define Nibbler_HPP_

    #include <SFML/Graphics.hpp>  
    #include <iostream>
    #include <fstream>
    #include <vector>  
    #include <ctime>  
    #include <cstdlib>
    #include <sstream>
    #include <thread>
    #include "IModuleGame.hpp"
    #include "IModuleDisplay.hpp"

    // class nibbler_display {   
    //     private:
    //         nibbler_l &logic;
    //         sf::RenderWindow window;
    //         sf::Event event;
    //         sf::Texture head_texture;
    //         sf::Texture blob_texture;
    //         sf::Texture wall_texture;
    //         sf::Texture death_texture;
    //         sf::Texture apple_texture;
    //         sf::Sprite head_sprite;
    //         sf::Sprite blob_sprite;
    //         sf::Sprite wall_sprite;
    //         sf::Sprite death_sprite;
    //         sf::Sprite apple_sprite;


    //     public:
    //         nibbler_display(nibbler_l &l);
    //         void draw();
    //         ~nibbler_display();
    //         void key_input();
    //         void move_nibbler(sf::Clock *clock);
    //         void create_head();
    //         void create_blob();
    //         void create_wall();
    //         void create_death();
    //         void create_apple();

    // };

    class Nibbler : public IGameModule {
        public:
            Nibbler();
            ~Nibbler();
            void init() override;
            void update() override;
            void eatfood();
            bool isGameOver() const;
            const std::vector<std::string>& getMap() const;
            std::vector <GameElement> getGameState() const;
            void handleInput(TrackPack keyCode);
            void setall(int w, int h, const std::string& m);

        private:
            std::vector<std::string> map;
            std::vector<std::pair<int, int>> nibbler;
            TrackPack direction;
            int x_food, y_food;
            int x, y;
            int nb_fruit;
            int score;
            std::vector <std::pair<int, int>> foods;
            int width;
            int height;
            bool is_ended;
            std::vector <GameElement> element;
            int time;
            std::string m;
            

    };

#endif /* !nibbler_HPP_ */
