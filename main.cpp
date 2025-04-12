/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** main
*/

#include "nibbler.hpp"
#include "sfml.hpp"
#include "Ncures.hpp"
// #include "sdl.hpp"
#include "Snake.hpp"

int main(int ac, char **av)
{
    Nibbler g_test;
    Sfml test;

    try {
        g_test.init();
        test.init(g_test.getGameState());
        TrackPack keycode;

        while (!g_test.isGameOver()) {
            test.handleInput();
            keycode = test.getEvent();
            g_test.handleInput(keycode);
            g_test.update();
        // std::cout << "GGGGGGGGGGG" << std::endl;
            test.update(g_test.getGameState());
            test.draw();
        }
    } catch (...) {
        std::cerr << "eeeeeeeeeeeeeeeeeeeeeeeeeeee" << std::endl;
    }
}