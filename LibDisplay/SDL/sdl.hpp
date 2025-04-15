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
#include "./../../IModuleDisplay.hpp"
#include <iostream>

using SDL_infos = std::tuple<int, int, int, int, SDL_Texture*>;

class Sdl : public IModuleDisplay {
    public:
        ~Sdl();
        Sdl();
        static Sdl* getInstance() {
            if (s_pInstance == nullptr) {
                s_pInstance = new Sdl();
            }
            return s_pInstance;
        }
        void init(std::vector <GameElement> configs) override;
        void handleInput() override;
        TrackPack getEvent() override;
        void draw() override;
        void update(std::vector <GameElement> configs) override;
        void stop() override;
        void drawSprite(SDL_infos info);
        void destroy() override;
    
    private:
        TrackPack keyPressed;
        SDL_Window *m_pWindow;
        SDL_Renderer *m_pRenderer;
        SDL_Event event;
        std::vector<SDL_infos> images;
        std::vector <GameElement> oldState;
        static Sdl *s_pInstance;
};

#endif /* !SDL_HPP_ */
