/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** nibbler
*/

#include "nibbler.hpp"

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

Nibbler::~Nibbler()
{

}

Nibbler::Nibbler()
{
}

void Nibbler::init()
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
    for (int i = 0; i < 4; i++) {
        int len = map.size();
        nibbler.push_back({x, y - i});
        element[(y * len) + x].setSymbol('O');
        map[y][x] = 'O';
    }
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
            element[(y_food * len_y) + x_food].setSymbol('X');
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
    if ((direction == UP && keyCode != DOWN) ||   
        (direction == DOWN && keyCode != UP) ||   
        (direction == LEFT && keyCode != RIGHT) ||   
        (direction == RIGHT && keyCode != LEFT)) {  
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
        return;
    }

    for (size_t i = 1; i < nibbler.size(); i++) {  
        if (nibbler[i] == std::make_pair(new_x, new_y)) {
            is_ended = false;
            return;
        }  
    }
    if (!nibbler.empty()) {
        map[head.second][head.first] = 'B';
        element[(head.second * len) + head.first].setSymbol('B');
    }

    nibbler.insert(nibbler.begin(), {new_x, new_y});
    element[(new_y * len) + new_x].setSymbol('O');
    map[new_y][new_x] = 'O';
    

    for (int i = 0; i < foods.size(); i++) {
        if (foods[i] == std::make_pair(new_x, new_y)) {
            score += 10;
            std::cout << "Score: " << score << std::endl;
            time += 10;
            is_ended = true;
            return;
        }
    }
    auto tail = nibbler.back();
    element[(tail.second * len) + tail.first].setSymbol(' ');
    map[tail.second][tail.first] = ' ';
    nibbler.pop_back();

    return;  
}  

const std::vector<std::string>& Nibbler::getMap() const
{  
    return map;
}

bool Nibbler::isGameOver() const
{
    return is_ended;
}

std::vector <GameElement> Nibbler::getGameState() const
{
    return element;
}

void Nibbler::setall(int w, int h, const std::string& filename)
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
    nb_fruit = 12;
    score = 0;
    time = 20;
    is_ended = false;
}

// void nibbler_display::create_head()
// {
//     if (!head_texture.loadFromFile("head.png")) {
//         std::cerr << "Error loading background image" << std::endl;
//         return;
//     }

//     float scale = 20.0f / 1024.0f;
//     head_sprite.setTexture(head_texture);
//     head_sprite.setScale(scale, scale);
// }

// void nibbler_display::create_blob()
// {
//     if (!blob_texture.loadFromFile("blob.png")) {
//         std::cerr << "Error loading background image" << std::endl;
//         return;
//     }

//     float scale = 20.0f / 512.0f;
//     blob_sprite.setTexture(blob_texture);
//     blob_sprite.setScale(scale, scale);
// }

// void nibbler_display::create_wall()
// {
//     if (!wall_texture.loadFromFile("wall.png")) {
//         std::cerr << "Error loading background image" << std::endl;
//         return;
//     }

//     float scale = 20.0f / 216.0f;
//     wall_sprite.setTexture(wall_texture);
//     wall_sprite.setScale(scale, scale);
// }

// void nibbler_display::create_death()
// {
//     if (!death_texture.loadFromFile("xx.png")) {
//         std::cerr << "Error loading background image" << std::endl;
//         return;
//     }

//     float scale = 20.0f / 1024.0f;
//     death_sprite.setTexture(death_texture);
//     death_sprite.setScale(scale, scale);
// }

// void nibbler_display::create_apple()
// {
//     if (!apple_texture.loadFromFile("apple.png")) {
//         std::cerr << "Error loading background image" << std::endl;
//         return;
//     }

//     float scale = 20.0f / 1024.0f;
//     apple_sprite.setTexture(apple_texture);
//     apple_sprite.setScale(scale, scale);
// }

// nibbler_display::nibbler_display(nibbler_l &l): logic(l), window(sf::VideoMode(963, 600), "nibbler Game")
// {
//     create_head();
//     create_blob();
//     create_wall();
//     create_death();
//     create_apple();
// }

// void nibbler_display::key_input()
// {
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
//         logic.direction('U');
//     }
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
//         logic.direction('D');
//     }
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
//         logic.direction('L');
//     }
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
//         logic.direction('R');
//     }
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
//         window.close();
//     }
// }

// void nibbler_display::move_nibbler(sf::Clock *clock)
// {
//     if ((*clock).getElapsedTime().asMilliseconds() >= 150) {  
//         if (!logic.move()) {  
//             std::cout << "Game Over!" << std::endl;  
//             window.close();  
//         }  
//         (*clock).restart();
//     }
// }

// void nibbler_display::draw()
// {
//     window.setFramerateLimit(10);  
//     const auto& map = logic.getMap();  
//     int cellSize = 20; 
//     sf::Clock clock;
//     sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));

//     while (window.isOpen()) {  
//         sf::Event event;  
//         while (window.pollEvent(event)) {  
//             if (event.type == sf::Event::Closed) {  
//                 window.close();  
//             }
//         }
//         key_input();
//         move_nibbler(&clock);
         
//         window.clear();  
//         for (size_t y = 0; y < map.size(); ++y) {  
//             for (size_t x = 0; x < map[y].size(); ++x) {  

//                 if (map[y][x] == 'O') {
//                     head_sprite.setPosition(x * cellSize, y * cellSize);
//                     window.draw(head_sprite); 
//                 } else if (map[y][x] == 'X') {  
//                     apple_sprite.setPosition(x * cellSize, y * cellSize);
//                     window.draw(apple_sprite);
//                 } else if (map[y][x] == '#'){  
//                     wall_sprite.setPosition(x * cellSize, y * cellSize);
//                     window.draw(wall_sprite);
//                 }else if (map[y][x] == 'B') {
//                     blob_sprite.setPosition(x * cellSize, y * cellSize);
//                     window.draw(blob_sprite);
//                 } else {
//                     cell.setPosition(x * cellSize, y * cellSize);
//                     cell.setFillColor(sf::Color::Black);
//                     window.draw(cell);
//                 }
//             }  
//         }  
//         window.display();
//     }  
// }

// nibbler_display::~nibbler_display()
// {

// }

// int main() {  
//     const int width = 49;
//     const int height = 31;  

//     std::string mapcontent = readFile("example.txt");
//     nibbler_l logic(width, height, mapcontent);
//     nibbler_display display(logic);
//     display.draw();

//     return 0;  
// }
