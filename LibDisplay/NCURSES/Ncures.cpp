/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** Ncures
*/

#include "Ncures.hpp"
#include <iostream>
#include <fstream>
#include <thread>

Ncurses* Ncurses::s_pInstance = 0;

Ncurses::Ncurses()
{
}

Ncurses::~Ncurses()
{
}

void Ncurses::init(std::vector <GameElement> configs)
{
    initscr();
    noecho();
    win = newwin(0,0,0,0);
    nodelay(win, true);
    oldState.clear();
    for (int a = 0; a < configs.size(); a++) {
        oldState.push_back(configs[a]);
    }
    keyPressed = NONE;
}

void Ncurses::draw()
{
    wclear(win);
    for (int i = 0; i < oldState.size(); i++) {
        int y = oldState[i].getPosY();
        int x = oldState[i].getPosX();
        char symbol = oldState[i].getSymbol();
        mvwaddch(win, y, x, symbol);
        // wrefresh(win);
    }
    wrefresh(win);
}

void Ncurses::update(std::vector<GameElement> configs)
{
    for (int a = 0; a < configs.size(); a++) {
        if (!(configs[a] == oldState[a])) {
            oldState[a].setPosX(configs[a].getPosX());
            oldState[a].setPosY(configs[a].getPosY());
            oldState[a].setSymbol(configs[a].getSymbol());
            oldState[a].setSpriteSize(configs[a].getSpriteSize());
            oldState[a].setSprite(configs[a].getSprite());
        }
    }
}

void Ncurses::handleInput()
{
    keypad(win, TRUE);
    int c = wgetch(win);
    keyPressed = NONE;
    if (c != ERR) {
        switch (c)
        {
            case KEY_UP:
                keyPressed = UP;
                break;
            case KEY_DOWN:
                keyPressed = DOWN;
                break;
            case KEY_LEFT:
                keyPressed = LEFT;
                break;
            case KEY_RIGHT:
                keyPressed = RIGHT;
                break;
            case 'l':
                keyPressed = LIB_LEFT;
                break;
            case 'r':
                keyPressed = LIB_RIGHT;
                break;
            case 'm':
                keyPressed = MENU;
                break;
            case 'u':
                keyPressed = GAME_LEFT;
                break;
            case 'd':
                keyPressed = GAME_RIGHT;
                break;
            case 'p':
                keyPressed = PAUSE;
                break;
            case 'n':
                keyPressed = RESTART;
                break;
            case 'q':
                keyPressed = QUIT;
                delwin(win);
                endwin();
                break;
            default:
                break;
        }
    }
}

TrackPack Ncurses::getEvent()
{
    return keyPressed;
}

void Ncurses::stop()
{
}

void Ncurses::destroy()
{
    oldState.clear();
    delwin(win);
    endwin();
}

extern "C" IModuleDisplay *createInstance() {
    return Ncurses::getInstance();
}

extern "C" void destroyInstance(IModuleDisplay* instance) {
    //delete instance;
}