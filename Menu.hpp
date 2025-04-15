#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include "TextureManager.hpp"
#include "TextRenderer.hpp"
#include "IModuleDisplay.hpp"
#include "LibDisplay/SDL/sdl.hpp"
#include "LibDisplay/SFML/sfml.hpp"

static TextRenderer *m_textRenderer;
enum class MenuState {SELECTING_GAME, SELECTING_LIB};

class Menu {
    public:
        void update(int value);
        void render(SDL_Renderer *render);
        void render(sf::RenderWindow *window, sf::Font *font);
        std::string getSelectedGame(){return m_games[GameIndex];};
        std::string getSelectedLib(){return m_libs[LibIndex];};
        bool isFinished() const {return m_isFinished;};
        int getGameIndex() {return GameIndex;};
        int getLibIndex() {return LibIndex;};
        void setGameIndex(int a) {
            if (!m_isFinished)
                GameIndex = a;
        }
        void setLibIndex(int b) {LibIndex = b;};
        static Menu* Instance() {
            if (s_pInstance == nullptr) {
                s_pInstance = new Menu();
            }
            return s_pInstance;
        }
    private:
        Menu(){
            GameIndex = -1;
            LibIndex = -1;
        };
        static Menu* s_pInstance;
        std::vector<std::string> m_games = {"Snake", "Nibbler"};
        std::vector<std::string> m_libs = {"SDL2", "SFML", "Ncurses"};
        int m_selectedGame = 0;
        int m_selectedLib = 0;
        MenuState m_state = MenuState::SELECTING_LIB;
        bool m_isFinished = false;
        int LibIndex;
        int GameIndex;
};

#endif