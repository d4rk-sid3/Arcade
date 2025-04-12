/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** nibbler
*/

#include "nibbler.hpp"

Nibbler::~Nibbler()
{

}

Nibbler::Nibbler()
{
}

void Nibbler::init()
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
        if (key == "PREVIOUS") {
            if (value == "DOWN") {
                previous = DOWN;
            } else if (value == "UP") {
                previous = UP;
            } else if (value == "LEFT") {
                previous = LEFT;
            } else if (value == "RIGHT") {
                previous = RIGHT;
            }
        }
        if (key == "HEAD_NIBBLER_X") {
            x = std::stoi(value);
        }
        if (key == "HEAD_NIBBLER_Y") {
            y = std::stoi(value);
        }
        if (key == "FOOD_X") {
            x_food = std::stoi(value);
        }
        if (key == "FOOD_Y") {
            y_food = std::stoi(value);
        }
        if (key == "NB_FOOD") {
            nb_fruit = std::stoi(value);
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
    map[y][x] = 'O';
    nibbler.push_back({x, y});
    for (int i = 0; i < 3; i++) {
        map[y - i - 1][x] = 'B';
        nibbler.push_back({x, y - i - 1});
    }
    createElement();
    eatfood();
}

void Nibbler::eatfood()
{  
    std::srand(std::time(nullptr));

    x_food = x;
    y_food = y;
    int len_x = map[0].size();
    int len_y = map.size();
    int a = 0;
    while (a < nb_fruit) {
        if (map[y_food][x_food] == ' ') {
            map[y_food][x_food] = 'X';
            foods.push_back({x_food, y_food});
            a++;
        }
        x_food = std::rand() % len_x;  
        y_food = std::rand() % len_y;
    }
}

void Nibbler::handleInput(TrackPack keyCode)
{
    auto head = nibbler.front();  
    int new_x = head.first;
    int new_y = head.second;

    if (keyCode == NONE)
        return;

    if (keyCode == UP) {
        new_y-=1;
    } else if (keyCode == DOWN) {
        new_y+=1;
    } else if (keyCode == LEFT) {
        new_x-=1;
    } else if (keyCode == RIGHT) {
        new_x+=1;
    }

    if (map[new_y][new_x] == '#') {
        direction = previous;
        return;
    }

    if ((direction == UP && keyCode != DOWN) ||   
        (direction == DOWN && keyCode != UP) ||   
        (direction == LEFT && keyCode != RIGHT) ||   
        (direction == RIGHT && keyCode != LEFT)) {
        previous = direction;
        direction = keyCode;  
    }
}

void Nibbler::update()
{  
    int len = map.size();
    auto head = nibbler.front();  
    int new_x = head.first;
    int new_y = head.second;

    if (direction == UP) {
        new_y-=1;
    } else if (direction == DOWN) {
        new_y+=1;
    } else if (direction == LEFT) {
        new_x-=1;
    } else if (direction == RIGHT) {
        new_x+=1;
    }
    
    for (size_t i = 1; i < nibbler.size(); i++) {
        if (nibbler[i] == std::make_pair(new_x, new_y)) {
            is_ended = true;
            createElement();
            return;
        }  
    }

    if (map[new_y][new_x] == '#') {
        createElement();
        return;
    }

    if (map[new_y][new_x] == 'X') {
        for (int i = 0; i < foods.size(); i++) {
            if (foods[i] == std::make_pair(new_x, new_y)) {
                score += 10;
                // std::cout << "Score: " << score << std::endl;
                time -= 10;
                map[head.second][head.first] = 'B';
                nibbler.insert(nibbler.begin(), {new_x, new_y});
                map[new_y][new_x] = 'O';
                foods.erase(foods.begin() + i);
                break;
            }
        }
    }
    
    if (map[new_y][new_x] == ' ') {
        map[head.second][head.first] = 'B';
        nibbler.insert(nibbler.begin(), {new_x, new_y});
        map[new_y][new_x] = 'O';
        auto tail = nibbler.back();
        map[tail.second][tail.first] = ' ';
        nibbler.pop_back();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    createElement();
    return;  
}

bool Nibbler::isGameOver() const
{
    return is_ended;
}

void Nibbler::createElement()
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
                elem.setSprite("./Games/Nibbler/wall.png");
            } else if (map[a][b] == 'O') {
                elem.setSprite("./Games/Nibbler/head.png");
            } else if (map[a][b] == 'X') {
                elem.setSprite("./Games/Nibbler/apple.png");
            } else if (map[a][b] == 'B') {
                elem.setSprite("./Games/Nibbler/blob.png");
            } else if (map[a][b] == ' ') {
                elem.setSprite("./Games/Nibbler/black.png");
            }
            element.emplace_back(elem);
        }
    }
}

std::vector <GameElement> Nibbler::getGameState() const
{
    return element;
}

int Nibbler::getScore() const
{
    return score;
}