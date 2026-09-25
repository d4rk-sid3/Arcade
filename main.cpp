/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** main
*/

#include "Core.hpp"

int handle_error(int ac, char **av)
{
    const std::vector <std::string> tab = {"./lib/arcade_ndk++.so", "./lib/arcade_aalib.so", "./lib/arcade_libcaca.so",
        "./lib/arcade_allegro5.so", "./lib/arcade_xlib.so", "./lib/arcade_gtk+.so", "./lib/arcade_sfml.so",
        "./lib/arcade_irrlicht.so", "./lib/arcade_opengl.so", "./lib/arcade_vulkan.so", "./lib/arcade_qt5.so"
        , "./lib/arcade_ncurses.so", "./lib/arcade_sdl2.so"};

    if (ac != 2) {
        std::cerr << "USAGE: " << av[0] << " ./lib/arcade_<graphics>.so" << std::endl;
        return 84;
    }
    std::ifstream flux(av[1]);
    if (!flux.is_open()) {
        std::cerr << "arcade: cannot open " << av[1] << std::endl;
        return 84;
    }
    flux.close();
    std::size_t i = 0;
    for (; i < tab.size(); i++) {
        if (av[1] == tab[i])
            break;
    }
    if (i == tab.size()) {
        std::cerr << "arcade: " << av[1] << " is not a known graphics library" << std::endl;
        return 84;
    }
    return 1;
}

int main(int ac, char **av)
{
    DLLoader<Ncurses> ncurses("./lib/arcade_ncurses.so");
    DLLoader<Sfml> sfml("./lib/arcade_sfml.so");
    DLLoader<Sdl> sdl("./lib/arcade_sdl2.so");
    DLLoader<Snake> snake("./lib/arcade_snake.so");
    DLLoader<Nibbler> nibbler("./lib/arcade_nibbler.so");

    if (handle_error(ac, av) == 84)
        return 84;
    std::vector<IModuleDisplay *> tmpDisp = {sfml.getInstance(), ncurses.getInstance(), sdl.getInstance()};
    std::vector<IGameModule *> tmpGame = {snake.getInstance(), nibbler.getInstance()};
    Core core(tmpGame, tmpDisp, 0, 0);
    TrackPack keycode = NONE;
    core.runMenu(2);
    core.runGame(keycode);
    return 0;
}
