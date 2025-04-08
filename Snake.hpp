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
    #include "../../IModuleGame.hpp"

class Snake : public IGameModule {
    public:
        Snake(int w, int h);
        ~Snake();
        void init() override;
        void update() override;
        void eatfood();
        const std::vector<std::string>& getMap() const;
        bool isGameOver() const;

        ////////////////
        int getScore() const;
        std::vector <GameElement> getGameState() const;
        void handleInput(TrackPack keyCode);

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
};

#endif /* !SNAKE_HPP_ */
