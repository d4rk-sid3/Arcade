/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** sdl
*/

#ifndef SDL_HPP_
#define SDL_HPP_
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include "IModuleDisplay.hpp"
#include <iostream>

using SDL_infos = std::tuple<int, int, int, int, SDL_Texture*>;

class Sdl : public IModuleDisplay {
    public:
        Sdl();
        ~Sdl();
        void init(std::vector <GameElement> configs) override;
        void handleInput() override;
        TrackPack getEvent() override;
        void draw() override;
        void update(std::vector <GameElement> configs) override;
        void stop() override;
        void drawSprite(SDL_infos info);
    private:
        TrackPack keyPressed;
        SDL_Window *m_pWindow;
        SDL_Renderer *m_pRenderer;
        SDL_Event event;
        std::vector<SDL_infos> images;
        std::vector <GameElement> oldState;
};

#endif /* !SDL_HPP_ */
