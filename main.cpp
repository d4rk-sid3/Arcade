/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** main
*/

#include "nibbler.hpp"
#include "sfml.hpp"

int main(int ac, char **av)
{
    Nibbler g_test;
    Sfml test;

    try {
        g_test.init();
        test.init(g_test.getGameState());

        while (!g_test.isGameOver()) {
            
        }

    } catch () {

    }
}