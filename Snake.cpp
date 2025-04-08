/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** Snake
*/

#include "Snake.hpp"

Snake::~Snake()
{
}

Snake::Snake(int w, int h): direction(DOWN), x(w / 2), y(h / 2), x_food(0),
    y_food(0), width(w), height(h), is_ended(false), score(0)
{
    init();
}

void Snake::init()
{
    map.resize(height, std::string(width, ' ')); 
    snake.push_back({x, y});  
    map[y][x] = 'O';  
    eatfood();
}

void Snake::eatfood()
{  
    std::srand(std::time(nullptr));

    x_food = x;
    y_food = y;
    while (map[y_food][x_food] != ' ') {
        x_food = std::rand() % map[0].size();  
        y_food = std::rand() % map.size();  
    } 
    map[y_food][x_food] = 'X'; 
}

void Snake::handleInput(TrackPack keyCode)
{  
    if ((direction == UP && keyCode != DOWN) ||   
        (direction == DOWN && keyCode != UP) ||   
        (direction == LEFT && keyCode != RIGHT) ||   
        (direction == RIGHT && keyCode != LEFT)) {  
        direction = keyCode;  
    }  
}

void Snake::update()
{  
    auto head = snake.front();  
    int new_x = head.first;  
    int new_y = head.second;  

    if (direction == UP) {
        new_y--;
    } else if (direction == DOWN) {
        new_y++;
    } else if (direction == LEFT) {
        new_x--;
    } else if (direction == RIGHT) {
        new_x++;
    }

    if (new_x < 0 || new_x >= map[0].size() || new_y < 0 || new_y >= map.size()) {
        is_ended = true; 
        return;
    }

    for (size_t i = 1; i < snake.size(); ++i) {  
        if (snake[i] == std::make_pair(new_x, new_y)) {  
            is_ended = true;
            return;
        }  
    }

    snake.insert(snake.begin(), {new_x, new_y});  
    if (new_x == x_food && new_y == y_food) {
        eatfood();  
    } else {  
        auto tail = snake.back();  
        map[tail.second][tail.first] = ' '; 
        snake.pop_back();  
    }  
    map[new_y][new_x] = 'O';
    return;  
}

const std::vector<std::string>& Snake::getMap() const
{  
    return map;  
}

bool Snake::isGameOver() const
{
    return is_ended;
}
