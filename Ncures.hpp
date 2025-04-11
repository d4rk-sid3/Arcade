/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** Ncures
*/

#ifndef NCURES_HPP_
#define NCURES_HPP_
#include "IModuleDisplay.hpp"
#include "ncurses.h"

class Ncurses : public IModuleDisplay {
    public:
        Ncurses();
        ~Ncurses();
        void init(std::vector <GameElement> configs) override;
        void handleInput() override;
        TrackPack getEvent() override;
        void draw() override;
        void update(std::vector <GameElement> configs) override;
        void stop() override;

    protected:
    private:
        std::vector <GameElement> oldState;
        TrackPack keyPressed;
        std::string map;
};

#endif /* !NCURES_HPP_ */
