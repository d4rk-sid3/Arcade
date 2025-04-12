/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** Sfml
*/

#include "sdl.hpp"

Sdl::Sdl()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        m_pWindow = SDL_CreateWindow("Nibbler", 0, 0, 1920, 1080, 0);
        m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
        SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);
    }
    return;
}

void Sdl::handleInput()
{   
    keyPressed = NONE;
    stop();
    SDL_PumpEvents(); //Refresh the keyboard
    const Uint8* keyboard = SDL_GetKeyboardState(NULL);

    if (keyboard[SDL_SCANCODE_UP])
        keyPressed =  UP;
    if (keyboard[SDL_SCANCODE_DOWN])
        keyPressed =  DOWN;
    if (keyboard[SDL_SCANCODE_LEFT])
        keyPressed =  LEFT;
    if (keyboard[SDL_SCANCODE_RIGHT])
        keyPressed =  RIGHT;
    //Tu dois checker ici si 'Q' a été appuyé
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
    //     window.close();
    // }
}

TrackPack Sdl::getEvent()
{
    return keyPressed;
}

void Sdl::init(std::vector <GameElement> configs)
{
    keyPressed = NONE;
    oldState.clear();
    for (int a = 0; a < configs.size(); a++) {
        oldState.push_back(configs[a]);
    }
    for (int i = 0; i < configs.size(); i++) {
        int size = configs[i].getSpriteSize();
        int posX = configs[i].getPosX();
        int posY = configs[i].getPosY();
        SDL_Surface* pTempSurface = IMG_Load(configs[i].getSprite().c_str());
        SDL_Texture* pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
        SDL_FreeSurface(pTempSurface);
        //std::cout << "X = " << posX << std::endl;
        //std::cout << "Y = " << posY << std::endl;
        images.push_back(std::make_tuple(posX * size, posY * size, size, size, pTexture));
    }
}

void Sdl::drawSprite(SDL_infos info)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = std::get<2>(info);
    srcRect.h = std::get<2>(info);
    destRect.w = std::get<2>(info);
    destRect.h = std::get<2>(info);
    destRect.x = std::get<0>(info);
    destRect.y = std::get<1>(info);
    SDL_RenderCopyEx(m_pRenderer, std::get<4>(info), &srcRect,
    &destRect, 0, 0, SDL_FLIP_NONE);
}
void Sdl::draw()
{
    //m_pWindow.setFramerateLimit(10);
    // SDL_Delay(20);
    handleInput();
    SDL_RenderClear(m_pRenderer);
    for (int i = 0; i < images.size(); i++)
        drawSprite(images[i]);
    SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Sdl::update(std::vector<GameElement> configs)
{
    for (int a = 0; a < configs.size(); a++) {
        if (!(configs[a] == oldState[a])) {
            oldState[a] = configs[a];
            oldState[a].setPosX(configs[a].getPosX());
            oldState[a].setPosY(configs[a].getPosY());
            oldState[a].setSymbol(configs[a].getSymbol());
            oldState[a].setSpriteSize(configs[a].getSpriteSize());
            oldState[a].setSprite(configs[a].getSprite());
            int size = oldState[a].getSpriteSize();
            int posX = oldState[a].getPosX();
            int posY = oldState[a].getPosY();
            SDL_Surface* pTempSurface = IMG_Load(oldState[a].getSprite().c_str());
            SDL_Texture* pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
            SDL_FreeSurface(pTempSurface);
            images[a] = std::make_tuple(posX * size, posY * size, size, size, pTexture);
        }
    }
}

Sdl::~Sdl()
{
}

void Sdl::stop()
{
    if(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            oldState.~vector();
            SDL_DestroyWindow(m_pWindow);
            SDL_DestroyRenderer(m_pRenderer);
            SDL_Quit();
        }
    }
    return;
}