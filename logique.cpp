/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** logique
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <ncurses.h>

class GameLogic {
private:
    std::vector<std::string> map;
    int player_x, player_y;

public:
    GameLogic(const std::string &filename) {
        loadMap(filename);
    }

    void loadMap(const std::string &filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << std::endl;
            exit(1);
        }

        std::string line;
        while (std::getline(file, line)) {
            map.push_back(line);
        }

        // Trouver la position initiale du joueur
        for (size_t y = 0; y < map.size(); ++y) {
            for (size_t x = 0; x < map[y].size(); ++x) {
                if (map[y][x] == 'P') {
                    player_x = x;
                    player_y = y;
                    return;
                }
            }
        }
    }

    const std::vector<std::string>& getMap() const {
        return map;
    }

    int getPlayerX() const {
        return player_x;
    }

    int getPlayerY() const {
        return player_y;
    }

    bool move(int dx, int dy) {
        int new_x = player_x + dx;
        int new_y = player_y + dy;

        if (map[new_y][new_x] == '#') return false;  // Collision avec un mur

        if (map[new_y][new_x] == 'X') {  // Vérifier si une brique est devant
            int next_x = new_x + dx;
            int next_y = new_y + dy;

            if (map[next_y][next_x] == ' ' || map[next_y][next_x] == 'O') {
                // Déplacer la brique
                map[next_y][next_x] = 'X';
                map[new_y][new_x] = 'P';
                map[player_y][player_x] = (map[player_y][player_x] == 'O') ? 'O' : ' ';
                player_x = new_x;
                player_y = new_y;
                return true;
            } else {
                return false;  // Impossible de pousser la brique
            }
        }

        // Déplacement simple
        map[new_y][new_x] = 'P';
        map[player_y][player_x] = (map[player_y][player_x] == 'O') ? 'O' : ' ';
        player_x = new_x;
        player_y = new_y;
        return true;
    }
};

class GameDisplay {
public:
    void draw(const GameLogic &logic) {
        clear();
        const auto& map = logic.getMap();
        for (size_t y = 0; y < map.size(); ++y) {
            mvprintw(y, 0, map[y].c_str());
        }
        refresh();
    }

    void run(GameLogic &logic) {
        initscr();
        noecho();
        curs_set(0);
        keypad(stdscr, TRUE);

        draw(logic);
        int ch;
        while ((ch = getch()) != 'q') {
            switch (ch) {
                case KEY_UP:
                    logic.move(0, -1);
                    break;
                case KEY_DOWN:
                    logic.move(0, 1);
                    break;
                case KEY_LEFT:
                    logic.move(-1, 0);
                    break;
                case KEY_RIGHT:
                    logic.move(1, 0);
                    break;
            }
            draw(logic);
        }

        endwin();
    }
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <map_file>\n";
        return 1;
    }

    GameLogic logic(argv[1]);
    GameDisplay display;
    display.run(logic);

    return 0;
}