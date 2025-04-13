/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

    #include <iostream>  
    #include <vector>  
    #include <ctime>  
    #include <cstdlib>  
    #include <thread>
    #include <fstream>
    #include <sstream>
    #include <thread>
    #include "IModuleGame.hpp"

class Snake : public IGameModule {
    public:
        Snake();
        ~Snake();
        void init(bool _restart) override;
        void update() override;
        void eatfood();
        bool isGameOver() const;
        int getScore() const;
        std::vector <GameElement> getGameState() const;
        void handleInput(TrackPack keyCode);
        void createElement();
        void createsavepath();
        bool check_xin();
        void setpaused() override;
        void destroy() override;

    private:
        std::vector<std::string> map;
        std::vector<std::pair<int, int>> snake;
        TrackPack direction;
        int x_food, y_food;
        int x, y;
        int width;
        int height;
        bool is_ended;
        int score;
        std::vector <GameElement> element;
        std::string m;
        int time;
        const std::string filepath = "SnakeConfig.txt";
        const std::string savefilepath = "SnakeSave.txt";
        bool is_paused;
        bool is_restart;
};

#endif /* !SNAKE_HPP_ */
