/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** Core
*/

#include "LibGames/Nibbler/nibbler.hpp"
#include "LibDisplay/NCURSES/Ncures.hpp"
#include "LibDisplay/SDL/sdl.hpp"
#include "LibDisplay/SFML/sfml.hpp"
#include "LibGames/Snake/Snake.hpp"
#include "loader.hpp"

enum update_return
{
    LOGIQUE,
    GAME,
    DISPLAY,
    CONFIG,
    EMPTY,
    QUITALL
};

class Core
{
private:
    const std::vector<std::string> lib_display = {"SFML", "Ncurses", "SDL"};
    const std::vector<std::string> lib_games = {"Nibbler", "Snake"};
    int current_game;
    int current_display;
    std::vector <IGameModule *> all_games;
    std::vector <IModuleDisplay *> all_display;
    TrackPack keycode;
    Menu *menu;

public:
    Core(std::vector <IGameModule*> _all_games, std::vector <IModuleDisplay*> _all_display,
        int game, int lib);
    ~Core();
    int get_lib_game() {return current_game;};
    int get_lib_disp() {return current_display;};
    void set_lib_game(int actual) {current_game = actual;};
    void set_lib_disp(int actual) {current_display = actual;};
    void runGame(TrackPack keycode);
    void runMenu(int value);
    update_return update(TrackPack keyCode);
    void destroyall();
    void setGame(int currentGame) {current_game = currentGame;};
    void setLib(int currentDisplay) {current_display = currentDisplay;};
};