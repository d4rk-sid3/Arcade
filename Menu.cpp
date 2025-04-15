#include "Menu.hpp"

Menu* Menu::s_pInstance = 0;

void Menu::update(int value)
{
    IModuleDisplay *instance;
    DLLoader<Sfml> sfml("./lib/arcade_sfml.so");
    DLLoader<Sdl> sdl("./lib/arcade_sdl2.so");

    if (value == 0) {
        instance = sdl.getInstance();
        instance->handleInput(1);
    }
    else if (value == 1) {
        instance = sfml.getInstance();
        instance->handleInput(1);
    }

    if (m_state == MenuState::SELECTING_GAME) {
        if (m_selectedGame < 0)
            m_selectedGame = 1;
        else if (m_selectedGame >= m_games.size())
            m_selectedGame = 0;
        else if (instance->getKeyPressed() == UP)
            m_selectedGame--;
        else if (instance->getKeyPressed() == DOWN)
            m_selectedGame++;
        else if (instance->getKeyPressed() == ENTER)
            setGameIndex(m_selectedGame);
        else if (instance->getKeyPressed() == LEFT ||
            instance->getKeyPressed() == RIGHT)
            m_state = MenuState::SELECTING_LIB;
    }
    else if (m_state == MenuState::SELECTING_LIB) {
        if (m_selectedLib < 0)
            m_selectedLib = 2;
        else if (m_selectedLib >= m_libs.size())
            m_selectedLib = 0;
        else if (instance->getKeyPressed() == UP)
            m_selectedLib--;
        else if (instance->getKeyPressed() == DOWN)
            m_selectedLib++;
        else if (instance->getKeyPressed() == ENTER)
            LibIndex = m_selectedLib;
        else if (instance->getKeyPressed() == LEFT ||
        instance->getKeyPressed() == RIGHT)
            m_state = MenuState::SELECTING_GAME;
    }
    if (GameIndex != -1 && LibIndex != -1)
        m_isFinished = true;
}

void Menu::render(SDL_Renderer *render)
{
    int xLib = 200;
    int xGame = 700;
    int yStart = 200;
    int lineHeight = 60;

    SDL_Color textColor = {255, 255, 255, 255}; //Blanc
    SDL_Color titleColor = {0, 0, 0, 0};
    SDL_SetRenderDrawColor(render, 93, 135, 201, 1);
    SDL_RenderClear(render);
    TextRenderer::Instance()->drawText("LIBRARIES", xLib + 45, yStart - 60, titleColor, render);
    TextRenderer::Instance()->drawText("GAMES", xGame + 60, yStart - 60, titleColor, render);

    for (int i = 0; i < m_games.size(); i++) {
        TextRenderer::Instance()->drawText(m_games[i], xGame, yStart + i * lineHeight, textColor, render);
        SDL_Rect textRect = {xGame, yStart + i * lineHeight, 200, 50};
        SDL_SetRenderDrawColor(render, 255, 0, 0, 0); // Rouge
        SDL_RenderDrawRect(render, &textRect);
        if (i == GameIndex) {
            SDL_SetRenderDrawColor(render, 201, 166, 93, 1); //Orange
            SDL_RenderFillRect(render, &textRect);
            TextRenderer::Instance()->drawText(m_games[i], xGame, yStart + i * lineHeight, textColor, render);
            if (i == m_selectedGame && m_state == MenuState::SELECTING_GAME) {
                SDL_SetRenderDrawColor(render, 0, 255, 0, 255); //Vert
                SDL_RenderDrawRect(render, &textRect);
            }
        }
        else if (m_state == MenuState::SELECTING_GAME && i == m_selectedGame) {
            SDL_SetRenderDrawColor(render, 0, 255, 0, 255); //Vert
            SDL_RenderDrawRect(render, &textRect);
        }
    }
    for (int i = 0; i < m_libs.size(); i++) {
        TextRenderer::Instance()->drawText(m_libs[i], xLib, yStart + i * lineHeight, textColor, render);
        SDL_Rect textRect = {xLib, yStart + i * lineHeight, 200, 50};
        SDL_SetRenderDrawColor(render, 255, 0, 0, 0); // Rouge
        SDL_RenderDrawRect(render, &textRect);
        if (i == LibIndex) {
            SDL_SetRenderDrawColor(render, 201, 166, 93, 1); //Orange
            SDL_RenderFillRect(render, &textRect);
            TextRenderer::Instance()->drawText(m_libs[i], xLib, yStart + i * lineHeight, textColor, render);
            if (i == m_selectedLib && m_state == MenuState::SELECTING_LIB) {
                SDL_SetRenderDrawColor(render, 0, 255, 0, 255); //Vert
                SDL_RenderDrawRect(render, &textRect);
            }
        }
        else if (m_state == MenuState::SELECTING_LIB && i == m_selectedLib) {
            SDL_SetRenderDrawColor(render, 0, 255, 0, 255); //Vert
            SDL_RenderDrawRect(render, &textRect);
        }
    }
    return;
}

void Menu::render(sf::RenderWindow *window, sf::Font *font)
{
    int xLib = 200;
    int xGame = 700;
    int yStart = 200;
    int lineHeight = 60;

    window->clear(sf::Color::Black);
    TextRenderer::Instance()->drawText("LIBRARIES", xLib + 45, yStart - 60, sf::Color::White, font, window);
    TextRenderer::Instance()->drawText("GAMES", xGame + 60, yStart - 60, sf::Color::White, font, window);
    for (int i = 0; i < m_games.size(); i++) {
        TextRenderer::Instance()->drawText(m_games[i], xGame, yStart + i * lineHeight, sf::Color::White, font, window);
        sf::RectangleShape textRect(sf::Vector2f(200, 50));
        textRect.setPosition(sf::Vector2f(xGame, yStart + i * lineHeight));
        textRect.setOutlineColor(sf::Color::Red);
        if (i == GameIndex) {
            sf::Color color = {201, 166, 93, 1};
            textRect.setFillColor(color);
            TextRenderer::Instance()->drawText(m_games[i], xGame, yStart + i * lineHeight, sf::Color::White, font, window);
            if (i == m_selectedGame && m_state == MenuState::SELECTING_GAME) {
                textRect.setOutlineColor(sf::Color::Green);
            }
        }
        else if (m_state == MenuState::SELECTING_GAME && i == m_selectedGame) {
            textRect.setOutlineColor(sf::Color::Green);
        }
        window->draw(textRect);
    }
    for (int i = 0; i < m_libs.size(); i++) {
        TextRenderer::Instance()->drawText(m_libs[i], xLib, yStart + i * lineHeight, sf::Color::White, font, window);
        sf::RectangleShape textRect(sf::Vector2f(200, 50));
        textRect.setPosition(sf::Vector2f(xLib, yStart + i * lineHeight));
        textRect.setOutlineColor(sf::Color::Red);
        if (i == GameIndex) {
            sf::Color color = {201, 166, 93, 1};
            textRect.setFillColor(color);
            TextRenderer::Instance()->drawText(m_libs[i], xLib, yStart + i * lineHeight, sf::Color::White, font, window);
            if (i == m_selectedGame && m_state == MenuState::SELECTING_GAME) {
                textRect.setOutlineColor(sf::Color::Green);
            }
        }
        else if (m_state == MenuState::SELECTING_GAME && i == m_selectedGame) {
            textRect.setOutlineColor(sf::Color::Green);
        }
        window->draw(textRect);
    }
    return;
}