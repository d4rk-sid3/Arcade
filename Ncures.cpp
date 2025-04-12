/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** Ncures
*/

#include "Ncures.hpp"
#include <iostream>
#include <fstream>

Ncurses::Ncurses()
{
}

Ncurses::~Ncurses()
{
    delwin(win);
    endwin();
}

void Ncurses::init(std::vector <GameElement> configs)
{
    initscr();
    noecho();
    win = newwin(0,0,0,0);
    // keypad(win, TRUE);
    nodelay(win, true);
    std::cout << "GGGGGGGGGGG" << std::endl;
    oldState.clear();
    for (int a = 0; a < configs.size(); a++) {
        oldState.push_back(configs[a]);
    }
    keyPressed = NONE;
}

void Ncurses::draw()
{   
    static bool check = false;
    // handleInput();

    if (!check) {
        wclear(win);
        for (int i = 0; i < oldState.size(); i++) {
            int y = oldState[i].getPosY();
            int x = oldState[i].getPosX();
            char symbol = oldState[i].getSymbol();
            mvwprintw(win, y, x,"%c", symbol);
        }
        wrefresh(win);
        check = true;
    }
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
            case 'q':
                endwin();
            default:
                break;
        }
    }
    std::ofstream outFile("example.txt");
    if (outFile.is_open()) {
        outFile << c << "      " << keyPressed << "\n";
        outFile.close();
    } else {
        std::cerr << "Impossible d'ouvrir le fichier";
    }
}

TrackPack Ncurses::getEvent()
{
    return keyPressed;
}

void Ncurses::stop()
{
}