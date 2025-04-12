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
        std::ifstream file(filepath);  
    if (!file) {  
        std::cerr << "Error opening file: " << filepath << std::endl;
        std::exit(84);
        return;  
    }  
    std::string line;
    std::string map_line;

    while (std::getline(file, line)) {
        std::stringstream l(line);
        std::string key;
        std::string value;
        std::getline(l, key, '=');
        std::getline(l, value, '=');
        if (key == "WIDTH") {
            width = std::stoi(value);
        }
        if (key == "HEIGHT") {
            height = std::stoi(value);
        }
        if (key == "DIRECTION") {
            if (value == "DOWN") {
                direction = DOWN;
            } else if (value == "UP") {
                direction = UP;
            } else if (value == "LEFT") {
                direction = LEFT;
            } else if (value == "RIGHT") {
                direction = RIGHT;
            }
        }
        if (key == "HEAD_SNAKE_X") {
            x = std::stoi(value);
        }
        if (key == "HEAD_SNAKE_Y") {
            y = std::stoi(value);
        }
        if (key == "FOOD_X") {
            x_food = std::stoi(value);
        }
        if (key == "FOOD_Y") {
            y_food = std::stoi(value);
        }
        if (key == "SCORE") {
            score = std::stoi(value);
        }
        if (key == "TIME") {
            time = std::stoi(value);
        }
        if (key == "IS_ENDED") {
            if (value == "FALSE") {
                is_ended = false;
            } else if (value == "TRUE") {
                is_ended = true;
            }
        }
        if (key == "MAP") {
            while (std::getline(file, map_line)) {
                map.push_back(map_line);
            }
        }
    }
    snake.push_back({x, y});
    map[y][x] = 'O';
    createElement();
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
    if (keyCode == NONE)
        return;
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

    if (map[new_y][new_x] == '#') {
        is_ended = true;
        createElement();
        return;
    }

    for (size_t i = 1; i < snake.size(); i++) {  
        if (snake[i] == std::make_pair(new_x, new_y)) {  
            is_ended = true;
            createElement();
            return;
        }  
    }

    map[head.second][head.first] = 'B';
    snake.insert(snake.begin(), {new_x, new_y});  
    if (new_x == x_food && new_y == y_food) {
        eatfood();
        time -= 10;
    } else {  
        auto tail = snake.back();
        map[tail.second][tail.first] = ' '; 
        snake.pop_back();  
    }
    map[new_y][new_x] = 'O';
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    createElement();
    return;  
}

bool Snake::isGameOver() const
{
    return is_ended;
}

std::vector <GameElement> Snake::getGameState() const
{
    return element;
}

void Snake::createElement()
{
    element.clear();
    for (int a = 0; a < map.size(); a++) {
        for (int b = 0; b < map[0].size(); b++) {
            GameElement elem;
            elem.setPosX(b);
            elem.setPosY(a);
            elem.setSymbol(map[a][b]);
            elem.setSpriteSize(20);
            if (map[a][b] == '#') {
                elem.setSprite("./Games/Snake/wall.png");
            } else if (map[a][b] == 'O') {
                elem.setSprite("./Games/Snake/head.png");
            } else if (map[a][b] == 'X') {
                elem.setSprite("./Games/Snake/apple.png");
            } else if (map[a][b] == 'B') {
                elem.setSprite("./Games/Snake/blob.png");
            } else if (map[a][b] == ' ') {
                elem.setSprite("./Games/Snake/black.png");
            }
            element.emplace_back(elem);
        }
    }
}

int Snake::getScore() const
{
    return score;
}
