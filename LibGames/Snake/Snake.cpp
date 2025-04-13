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

Snake::Snake()
{
}

void Snake::createsavepath()
{
    std::ofstream outFile(savefilepath, std::ios::trunc);
    if (outFile.is_open()) {
        outFile << "WIDTH=" << width << std::endl;
        outFile << "HEIGHT=" << height << std::endl;
        if (direction == DOWN) {
            outFile << "DIRECTION=" << "DOWN" << std::endl;
        } else if (direction == UP) {
            outFile << "DIRECTION=" << "UP" << std::endl;
        } else if (direction == LEFT) {
            outFile << "DIRECTION=" << "LEFT" << std::endl;
        } else if (direction == RIGHT) {
            outFile << "DIRECTION=" << "RIGHT" << std::endl;
        }
        outFile << "HEAD_SNAKE_X=" << snake[0].first << std::endl;
        outFile << "HEAD_SNAKE_Y=" << snake[0].second << std::endl;
        outFile << "FOOD_X=" << x_food << std::endl;
        outFile << "FOOD_Y=" << y_food << std::endl;
        outFile << "SCORE=" << score << std::endl;
        outFile << "TIME=" << time << std::endl;
        outFile << "IS_ENDED=" << is_ended << std::endl;
        outFile << "MAP=" << std::endl;
        for (int i = 0; i < map.size(); i++) {
            outFile << map[i] << std::endl;
        }
        outFile.close();
    } else {
        std::cerr << "Impossible d'ouvrir le fichier";
    }
}

void Snake::init(bool _restart)
{
    std::string filetoopen;
    std::ifstream outFile(savefilepath);
    if (outFile.is_open()) {
        filetoopen = savefilepath;
        outFile.close();
    } else {
        filetoopen = filepath;
    }
    if (_restart == true) {
        filetoopen = filepath;
    }
    std::ifstream file(filetoopen);  
    if (!file) {  
        std::cerr << "Error opening file: " << filetoopen << std::endl;
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
    is_paused = false;
    snake.push_back({x, y});
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 'B') {
                snake.push_back({j, i});
            }
        }
    }
    createElement();
    if (!check_xin())
        eatfood();
}

bool Snake::check_xin()
{
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 'X')
                return true;
        }
    }
    return false;
}

void Snake::eatfood()
{
    std::srand(std::time(nullptr));

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

    if (is_paused) {
        createElement();
        return;
    }
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
    createElement();
    createsavepath();
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
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

int Snake::getScore() const
{
    return score;
}

void Snake::setpaused()
{
    is_paused = !is_paused;
}

void Snake::destroy()
{
    map.clear();
    snake.clear();
    element.clear();
}
