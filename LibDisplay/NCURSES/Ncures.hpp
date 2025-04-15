/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** Ncures
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_
#include "./../../IModuleDisplay.hpp"
#include "ncurses.h"
#include <iostream>

class Ncurses : public IModuleDisplay {
    public:
    ~Ncurses();
    Ncurses();
    static Ncurses* getInstance() {
        if (s_pInstance == nullptr) {
            s_pInstance = new Ncurses();
        }
        return s_pInstance;
    }
    void init(std::vector <GameElement> configs) override;
    void handleInput() override;
    TrackPack getEvent() override;
    void draw() override;
    void update(std::vector <GameElement> configs) override;
    void stop() override;
    void destroy() override;
    
    protected:
    private:
        std::vector <GameElement> oldState;
        TrackPack keyPressed;
        std::string map;
        WINDOW *win;
        static Ncurses *s_pInstance;
};

#endif /* !NCURES_HPP_ */
