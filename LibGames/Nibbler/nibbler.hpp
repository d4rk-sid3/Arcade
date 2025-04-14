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
#include "./../../IModuleGame.hpp"

class Nibbler : public IGameModule {
    public:
        Nibbler();
        ~Nibbler();
        void init(state check) override;
        void update() override;
        void eatfood();
        bool isGameOver() const;
        std::vector <GameElement> getGameState() const;
        void handleInput(TrackPack keyCode);
        void createElement();
        int getScore() const;
        void createsavepath();
        bool check_xin();
        void setpaused() override;
        void destroy() override;
 
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
        std::clock_t start;
        double duration;
        const std::string filepath = "NibblerConfig.txt";
        const std::string savefilepath = "NibblerSave.txt";
        const std::string overfilepath = "gameover.txt";
        TrackPack previous;
        bool is_paused;
        bool is_restart;
        
};
#endif /* !nibbler_HPP_ */
