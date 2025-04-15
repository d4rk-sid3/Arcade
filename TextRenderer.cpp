#include "TextRenderer.hpp"
#include <iostream>
#include <errno.h>

TextRenderer* TextRenderer::s_pInstance = 0;

TextRenderer::TextRenderer(const std::string& fontPath, int fontSize)
{
    m_font = TTF_OpenFont(fontPath.c_str(), fontSize);
}

TextRenderer::~TextRenderer()
{
    if (m_font) {
        TTF_CloseFont(m_font);
    }
}

void TextRenderer::drawText(const std::string& text, int x, int y,
    SDL_Color color, SDL_Renderer *render)
{
    if (!m_font)
        return;
    SDL_Surface *surface = TTF_RenderText_Solid(m_font, text.c_str(), color);
    if (!surface) {
        return;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(render, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        return;
    }
    SDL_Rect dstRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(render, texture, nullptr, &dstRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    return;
}

void TextRenderer::drawText(const std::string& text, int x, int y,
    sf::Color color, sf::Font *font, sf::RenderWindow *window)
{
    sf::Text *test = new sf::Text;

    test->setFont(*font);
    test->setString(text);
    test->setFillColor(color);
    test->setPosition(x, y);
    test->setCharacterSize(24);
    window->draw(*test);
}