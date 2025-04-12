/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** main
*/

#include "nibbler.hpp"
#include "sfml.hpp"
#include "Ncures.hpp"
#include "sdl.hpp"
#include "Snake.hpp"

class Core
{
private:
    const std::vector lib_display = {"SFML", "Ncurses", "SDL"};
    const std::vector lib_games = {"Nibbler", "Snake"};
    int current_game;
    int current_display;

    std::vector <IGameModule *> all_games;
    std::vector <IModuleDisplay *> all_display;
    TrackPack keycode;

public:
    Core(std::vector <IGameModule*> _all_games, std::vector <IModuleDisplay*> _all_display,
        int game, int lib);
    ~Core();
    int get_lib_game() {return current_game;};
    int get_lib_disp() {return current_display;};
    void set_lib_game(int actual) {current_game = actual;};
    void set_lib_disp(int actual) {current_display = actual;};
    void runGame(IGameModule *game, TrackPack keycode);
    void update(TrackPack keyCode);
        
};

Core::Core(std::vector <IGameModule*> _all_games, std::vector <IModuleDisplay*> _all_display,
    int _game, int _lib) : all_display(_all_display), all_games(_all_games),
    current_game(_game), current_display(_lib)
{
}

Core::~Core()
{
}

void Core::update(TrackPack keyCode)
{
    if (keyCode == LIB_LEFT) {
        all_display[current_display]->destroy();
        current_display -= 1;
    }
    if (keyCode == LIB_RIGHT) {
        all_display[current_display]->destroy();
        current_display += 1;
    }
    if (current_display < 0)
        current_display = 2;
    else if (current_display > 2)
        current_display = 0;
    

}

void Core::runGame(IGameModule *game, TrackPack keycode)
{
    try {
        game->init();
        all_display[current_display]->init(game->getGameState());
        TrackPack keycode;
        int a = 0;

        while (!game->isGameOver()) {
            all_display[current_display]->handleInput();
            keycode = all_display[current_display]->getEvent();
            if (keycode == QUIT)
                break;
            game->handleInput(keycode);
            game->update();
            all_display[current_display]->update(game->getGameState());
            all_display[current_display]->draw();
        }
    } catch (...) {
        std::cerr << "eeeeeeeeeeeeeeeeeeeeeeeeeeee" << std::endl;
    }
}

int main(void)
{
   std::vector<IModuleDisplay *> tmpDisp = {Sfml::getInstance(), Ncurses::getInstance(), Sdl::getInstance()};
   std::vector<IGameModule *> tmpGame = {new Snake, new Nibbler};
   Core core(tmpGame, tmpDisp, 0, 0);
   TrackPack keycode;

    core.update(keycode);
    core.runGame(tmpGame[0] ,keycode);
}