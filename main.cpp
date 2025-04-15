/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** main
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

public:
    Core(std::vector <IGameModule*> _all_games, std::vector <IModuleDisplay*> _all_display,
        int game, int lib);
    ~Core();
    int get_lib_game() {return current_game;};
    int get_lib_disp() {return current_display;};
    void set_lib_game(int actual) {current_game = actual;};
    void set_lib_disp(int actual) {current_display = actual;};
    void runGame(TrackPack keycode);
    update_return update(TrackPack keyCode);
    void destroyall();
        
};

Core::Core(std::vector <IGameModule*> _all_games, std::vector <IModuleDisplay*> _all_display,
    int _game, int _lib) : all_display(_all_display), all_games(_all_games),
    current_game(_game), current_display(_lib)
{
}

Core::~Core()
{
}

void Core::destroyall()
{
    all_games[current_game]->destroy();
    for (int i = 0; i < all_games.size(); i++) {
        delete all_games[i];
    }
    all_display[current_display]->destroy();
    for (int i = 0; i < all_display.size(); i++) {
        delete all_display[i];
    }
}

update_return Core::update(TrackPack keyCode)
{
    if (keyCode == UP)
        return LOGIQUE;
    else if (keyCode == DOWN)
        return LOGIQUE;
    else if (keyCode == LEFT)
        return LOGIQUE;
    else if (keyCode == RIGHT)
        return LOGIQUE;
    else if (keyCode == QUIT) {
        destroyall();
        return QUITALL;
    } else if (keyCode == LIB_LEFT) {
        all_games[current_game]->setpaused();
        all_display[current_display]->destroy();
        current_display -= 1;
        return DISPLAY;
    } else if (keyCode == LIB_RIGHT) {
        all_games[current_game]->setpaused();
        all_display[current_display]->destroy();
        current_display += 1;
        return DISPLAY;
    } else if (keyCode == MENU)
        return CONFIG;
    else if (keyCode == GAME_LEFT) {
        all_games[current_game]->destroy();
        current_game -= 1;
        return GAME;
    } else if (keyCode == GAME_RIGHT) {
        all_games[current_game]->destroy();
        current_game += 1;
        return GAME;
    } else if (keyCode == PAUSE)
        return CONFIG;
    else if (keyCode == RESTART)
        return CONFIG;
    else if (keyCode == NONE)
        return LOGIQUE;
    return EMPTY;
}

void Core::runGame(TrackPack keycode)
{
    // try {
        bool isquited = false;
        all_games[current_game]->init(SAVE);
        all_display[current_display]->init(all_games[current_game]->getGameState());
        int a = 0;

        while (!isquited) {
            all_display[current_display]->handleInput();
            keycode = all_display[current_display]->getEvent();
            update_return check;
            
            check = update(keycode);
            if (check == LOGIQUE) {
                all_games[current_game]->handleInput(keycode);
                all_games[current_game]->update();
                all_display[current_display]->update(all_games[current_game]->getGameState());
                all_display[current_display]->draw();
            }
            if (check == DISPLAY) {
                if (current_display < 0)
                    current_display = 2;
                else if (current_display > 2)
                    current_display = 0;
                all_games[current_game]->setpaused();
                all_display[current_display]->init(all_games[current_game]->getGameState());
            }
            if (check == QUITALL) {
                isquited = true;
                break;
            }
            if (check == CONFIG) {
                if (keycode == PAUSE) {
                    all_games[current_game]->setpaused();
                }
                if (keycode == RESTART) {
                    all_games[current_game]->destroy();
                    all_games[current_game]->init(REST);
                }
            }
            if (check == GAME) {
                 if (current_game < 0)
                    current_game = 1;
                else if (current_game > 1)
                    current_game = 0;
                all_games[current_game]->init(SAVE);
            }
            if (all_games[current_game]->isGameOver()) {
                all_games[current_game]->destroy();
                all_games[current_game]->init(OVER);
            }
        }
    // } catch (...) {
    //     std::cerr << "eeeeeeeeeeeeeeeeeeeeeeeeeeee" << std::endl;
    // }
}

int main(int ac, char **av)
{
    DLLoader<Ncurses> ncurses("./lib_ncurses.so");
    DLLoader<Sfml> sfml("./lib_sfml.so");
    DLLoader<Sdl> sdl("./lib_sdl.so");
    DLLoader<Snake> snake("./lib_snake.so");
    DLLoader<Nibbler> nibbler("./lib_nibbler.so");

    const std::vector <std::string> tab = {"arcade_ndk++.so", "arcade_aalib.so", "arcade_libcaca.so",
        "arcade_allegro5.so", "arcade_xlib.so", "arcade_gtk+.so", "arcade_sfml.so",
        "arcade_irrlicht.so", "arcade_opengl.so", "arcade_vulkan.so", "arcade_qt5.so"};

    if (ac != 2) {
        return 84;
    }

    std::ifstream flux(av[1]);

    if (flux.is_open()) {
        std::cout << "Le fichier existe !" << std::endl;
        flux.close();
    } else
        return 84;

    for (int i = 0; i < tab.size(); i++) {
        if (av[1] == tab[i])
    }

    std::vector<IModuleDisplay *> tmpDisp = {sfml.getInstance(), ncurses.getInstance(), sdl.getInstance()};
    std::vector<IGameModule *> tmpGame = {snake.getInstance(), nibbler.getInstance()};

    Core core(tmpGame, tmpDisp, 0, 0);
    TrackPack keycode = NONE;

    core.runGame(keycode);
}
