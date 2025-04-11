/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** Ncures
*/

#include "Ncures.hpp"

Ncurses::Ncurses()
{
}

Ncurses::~Ncurses()
{
}

void Ncurses::init(std::vector <GameElement> configs)
{
    initscr();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    noecho();
    oldState.clear();
    for (int a = 0; a < configs.size(); a++) {
        oldState.push_back(configs[a]);
    }
}

void Ncurses::draw()
{
    handleInput();
    clear();
    for (int i = 0; i < oldState.size(); i++) {
        move(oldState[i].getPosY(), oldState[i].getPosX());
        addch(oldState[i].getSymbol());
        // mvprintw(oldState[i].getPosY(), oldState[i].getPosX(),"%c", oldState[i].getSymbol());
    }
    refresh();
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
    char c = getch();

    switch (c)
    {
        case (char) KEY_UP:
            keyPressed =  UP;
            break;
        case (char) KEY_DOWN:
            keyPressed =  DOWN;
            break;
        case (char) KEY_LEFT:
            keyPressed =  LEFT;
            break;
        case (char) KEY_RIGHT:
            keyPressed =  RIGHT;
            break;
        case 'q':
            endwin();
        default:
            break;
    }
}

TrackPack Ncurses::getEvent()
{
    return keyPressed;
}

void Ncurses::stop()
{
}