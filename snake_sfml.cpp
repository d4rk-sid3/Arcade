/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** snake_sfml
*/

#include "snake.hpp"

snake_l::snake_l(int w, int h): d('D'), x(w / 2), y(h / 2), x_food(0), y_food(0)
{
    map.resize(h, std::string(w, ' ')); 
    snake.push_back({x, y});  
    map[y][x] = 'O';  
    eatfood();  
}  

void snake_l::eatfood()
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

void snake_l::direction(char newDirection)
{  
    if ((d == 'U' && newDirection != 'D') ||   
        (d == 'D' && newDirection != 'U') ||   
        (d == 'L' && newDirection != 'R') ||   
        (d == 'R' && newDirection != 'L')) {  
        d = newDirection;  
    }  
}  

bool snake_l::move()
{  
    auto head = snake.front();  
    int new_x = head.first;  
    int new_y = head.second;  

    if (d == 'U') {
        new_y--;
    } else if (d == 'D') {
        new_y++;
    } else if (d == 'L') {
        new_x--;
    } else if (d == 'R') {
        new_x++;
    }

    if (new_x < 0 || new_x >= map[0].size() || new_y < 0 || new_y >= map.size()) {  
        return false;
    }

    for (size_t i = 1; i < snake.size(); ++i) {  
        if (snake[i] == std::make_pair(new_x, new_y)) {  
            return false;
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
    return true;  
}  

const std::vector<std::string>& snake_l::getMap() const
{  
    return map;  
}   

snake_l::~snake_l()
{

}

snake_display::snake_display(snake_l &l): logic(l), window(sf::VideoMode(800, 600), "Snake Game")
{
}

void snake_display::key_input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        logic.direction('U');
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        logic.direction('D');
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        logic.direction('L');
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        logic.direction('R');
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        window.close();
    }
}

void snake_display::move_snake(sf::Clock *clock)
{
    if ((*clock).getElapsedTime().asMilliseconds() >= 150) {  
        if (!logic.move()) {  
            std::cout << "Game Over!" << std::endl;  
            window.close();  
        }  
        (*clock).restart();
    }
}

void snake_display::draw()
{
    window.setFramerateLimit(10);  
    const auto& map = logic.getMap();  
    int cellSize = 20; 
    sf::Clock clock;

    while (window.isOpen()) {  
        sf::Event event;  
        while (window.pollEvent(event)) {  
            if (event.type == sf::Event::Closed) {  
                window.close();  
            }
        }
        key_input();
        move_snake(&clock);
         
        window.clear();  
        for (size_t y = 0; y < map.size(); ++y) {  
            for (size_t x = 0; x < map[y].size(); ++x) {  
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));  
                cell.setPosition(x * cellSize, y * cellSize);  

                if (map[y][x] == 'O') {  
                    cell.setFillColor(sf::Color::Green);  
                } else if (map[y][x] == 'X') {  
                    cell.setFillColor(sf::Color::Red); 
                } else {  
                    cell.setFillColor(sf::Color::Black);
                }  
                window.draw(cell);  
            }  
        }  
        window.display();  
    }  
}

snake_display::~snake_display()
{

}

int main() {  
    const int width = 40;
    const int height = 30;  

    snake_l logic(width, height);
    snake_display display(logic);
    display.draw();

    return 0;  
}
