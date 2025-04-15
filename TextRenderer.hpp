#ifndef TEXT_RENDERER_HPP
#define TEXT_RENDERER_HPP

#include <string>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SFML/Graphics.hpp>

class TextRenderer {
public:
    static TextRenderer* Instance() {
        if (s_pInstance == nullptr) {
            s_pInstance = new TextRenderer("assets/ROMANS.ttf", 24);
        }
        return s_pInstance;
    }
    ~TextRenderer();
    void drawText(const std::string& text, int x, int y,
        SDL_Color color, SDL_Renderer *render);
    void drawText(const std::string& text, int x, int y,
        sf::Color color, sf::Font *font, sf::RenderWindow *window);
private:
    TextRenderer(const std::string& fontPath, int fontSize);
    static TextRenderer* s_pInstance;
    TTF_Font *m_font;
};

#endif