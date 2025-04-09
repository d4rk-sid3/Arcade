/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** Snake
*/

#include "Snake.hpp"

std::string readFile(const std::string& filename)
{  
    std::ifstream file(filename);  
    if (!file) {  
        std::cerr << "Error opening file: " << filename << std::endl;  
        return "";  
    }  
    std::string content;  
    std::string line;

    while (std::getline(file, line)) {  
        content += line + "\n";
    }  
    return content;  
}  

std::vector<std::string> readtable(const std::string& m)
{
    std::vector<std::string> newmap;
    std::istringstream stream(m);
    std::string line;
    
    while (std::getline(stream, line)) {
        newmap.push_back(line);
    }
    return newmap;
}

Snake::~Snake()
{
}

Snake::Snake()
{
}

void Snake::init()
{
    for (int a = 0; a < map.size(); a++) {
        for (int b = 0; b < map[0].size(); b++) {
            GameElement elem;
            elem.setPosX(b);
            elem.setPosY(a);
            elem.setSymbol(map[a][b]);
            if (map[a][b] == '#') {
                elem.setSprite("Games/Nibbler/wall.png");
            } else if (map[a][b] == 'O') {
                elem.setSprite("Games/Nibbler/head.png");
            } else if (map[a][b] == 'X') {
                elem.setSprite("Games/Nibbler/apple.png");
            } else if (map[a][b] == 'B') {
                elem.setSprite("Games/Nibbler/blob.png");
            }
            element.push_back(elem);
        }
    }
    int len = map.size();
    snake.push_back({x, y});
    element[(y * len) + x].setSymbol('O');
    map[y][x] = 'O';  
    eatfood();
}

void Snake::eatfood()
{
    int len = map.size();
    std::srand(std::time(nullptr));

    x_food = x;
    y_food = y;
    while (map[y_food][x_food] != ' ') {
        x_food = std::rand() % map[0].size();  
        y_food = std::rand() % map.size();  
    }
    element[(y_food * len) + x_food].setSymbol('X');
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
    int len = map.size();
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

    for (size_t i = 1; i < snake.size(); i++) {  
        if (snake[i] == std::make_pair(new_x, new_y)) {  
            is_ended = true;
            return;
        }  
    }

    if (!snake.empty()) {
        map[head.second][head.first] = 'B';
        element[(head.second * len) + head.first].setSymbol('B');
    }
    snake.insert(snake.begin(), {new_x, new_y});  
    if (new_x == x_food && new_y == y_food) {
        eatfood();  
    } else {  
        auto tail = snake.back();
        element[(tail.second * len) + tail.first].setSymbol(' ');
        map[tail.second][tail.first] = ' '; 
        snake.pop_back();  
    }
    element[(new_y * len) + new_x].setSymbol('O');
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

std::vector <GameElement> Snake::getGameState() const
{
    return element;
}

void Snake::setall(int w, int h, const std::string& filename)
{
    width = w;
    height = h;
    m = filename;
    direction = DOWN;
    x = (width / 2);
    y = (height / 2);
    x_food = 0;
    y_food = 0;
    map = readtable(m);
    score = 0;
    time = 20;
    is_ended = false;
}
