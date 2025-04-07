/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** snake_sfml
*/

#include "snake.hpp"

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

snake_l::snake_l(int w, int h, const std::string& m): d('D'), x(w / 2), y(h / 2), x_food(0), y_food(0), map(readtable(m))
{
    snake.push_back({x, y});  
    map[y][x] = 'O';
    eatfood();
}  

void snake_l::eatfood()
{  
    std::srand(std::time(nullptr));

    x_food = x;
    y_food = y;
    int len_x = map[0].size();
    int len_y = map.size();
        while (map[y_food][x_food] != ' ') {
            x_food = std::rand() % len_x;  
            y_food = std::rand() % len_y;
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

    if (map[new_y][new_x] == '#') {
        return false;
    }

    for (size_t i = 1; i < snake.size(); ++i) {  
        if (snake[i] == std::make_pair(new_x, new_y)) {  
            return false;
        }  
    }
    if (!snake.empty()) {
        map[head.second][head.first] = 'B';
    }

    snake.insert(snake.begin(), {new_x, new_y});
    map[new_y][new_x] = 'O';

    if (new_x == x_food && new_y == y_food) {  
        eatfood();  
    } else {  
        auto tail = snake.back();  
        map[tail.second][tail.first] = ' '; 
        snake.pop_back();  
    }
    return true;  
}  

const std::vector<std::string>& snake_l::getMap() const
{  
    return map;  
}   

snake_l::~snake_l()
{

}

void snake_display::create_head()
{
    if (!head_texture.loadFromFile("head.png")) {
        std::cerr << "Error loading background image" << std::endl;
        return;
    }

    float scale = 20.0f / 1024.0f;
    head_sprite.setTexture(head_texture);
    head_sprite.setScale(scale, scale);
}

void snake_display::create_blob()
{
    if (!blob_texture.loadFromFile("blob.png")) {
        std::cerr << "Error loading background image" << std::endl;
        return;
    }

    float scale = 20.0f / 512.0f;
    blob_sprite.setTexture(blob_texture);
    blob_sprite.setScale(scale, scale);
}

void snake_display::create_wall()
{
    if (!wall_texture.loadFromFile("wall.png")) {
        std::cerr << "Error loading background image" << std::endl;
        return;
    }

    float scale = 20.0f / 216.0f;
    wall_sprite.setTexture(wall_texture);
    wall_sprite.setScale(scale, scale);
}

void snake_display::create_death()
{
    if (!death_texture.loadFromFile("xx.png")) {
        std::cerr << "Error loading background image" << std::endl;
        return;
    }

    float scale = 20.0f / 1024.0f;
    death_sprite.setTexture(death_texture);
    death_sprite.setScale(scale, scale);
}

void snake_display::create_apple()
{
    if (!apple_texture.loadFromFile("apple.png")) {
        std::cerr << "Error loading background image" << std::endl;
        return;
    }

    float scale = 20.0f / 1024.0f;
    apple_sprite.setTexture(apple_texture);
    apple_sprite.setScale(scale, scale);
}

snake_display::snake_display(snake_l &l): logic(l), window(sf::VideoMode(963, 600), "Snake Game")
{
    create_head();
    create_blob();
    create_wall();
    create_death();
    create_apple();
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
    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));

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

                if (map[y][x] == 'O') {
                    head_sprite.setPosition(x * cellSize, y * cellSize);
                    window.draw(head_sprite); 
                } else if (map[y][x] == 'X') {  
                    apple_sprite.setPosition(x * cellSize, y * cellSize);
                    window.draw(apple_sprite);
                } else if (map[y][x] == '#'){  
                    wall_sprite.setPosition(x * cellSize, y * cellSize);
                    window.draw(wall_sprite);
                }else if (map[y][x] == 'B') {
                    blob_sprite.setPosition(x * cellSize, y * cellSize);
                    window.draw(blob_sprite);
                } else {
                    cell.setPosition(x * cellSize, y * cellSize);
                    cell.setFillColor(sf::Color::Black);
                    window.draw(cell);
                }
            }  
        }  
        window.display();
    }  
}

snake_display::~snake_display()
{

}

int main() {  
    const int width = 49;
    const int height = 31;  

    std::string mapcontent = readFile("example.txt");
    snake_l logic(width, height, mapcontent);
    snake_display display(logic);
    display.draw();

    return 0;  
}
