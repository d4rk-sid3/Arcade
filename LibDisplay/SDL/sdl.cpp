/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** Sfml
*/

#include "sdl.hpp"

Sdl* Sdl::s_pInstance = 0;

Sdl::Sdl()
{
}

void Sdl::init_menu()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        m_pWindow = SDL_CreateWindow("Menu", 0, 0, 1920, 1080, 0);
        m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
        SDL_SetRenderDrawColor(m_pRenderer,0,0,0,0);
    }
    TTF_Init();
    TextureManager::Instance()->load("assets/background.jpeg", "background", m_pRenderer);
    TextureManager::Instance()->load("assets/borne.png", "borne", m_pRenderer);
    TextureManager::Instance()->load("assets/player.png", "player", m_pRenderer);
    TextureManager::Instance()->load("assets/Untitled1.png", "message", m_pRenderer);
}

void Sdl::update_menu()
{
    if (Menu::Instance()->isFinished()) {
        current_a = Menu::Instance()->getGameIndex();
        current_b = Menu::Instance()->getLibIndex();
        //std::cout << "a" << current_a << std::endl;
        //std::cout << "b" << current_b << std::endl;
        keyPressed = QUIT;
        return;
    }
    if (Player::Instance()->getFocus() == Focus::MENU) {
        Menu::Instance()->update(0);
        return;
    }
    if (Player::Instance()->getFocus() == Focus::PLAYER) {
        Player::Instance()->update(0);
        return;
    }
    Player::Instance()->update_name(0);
    Player::Instance()->adjust_letters_position();
}

void Sdl::draw_menu()
{
    SDL_RenderClear(m_pRenderer);
    if (Player::Instance()->getFocus() == Focus::MENU) {
        Menu::Instance()->render(m_pRenderer);
        SDL_RenderPresent(m_pRenderer); // draw to the screen
        return;
    }
    if (Player::Instance()->getFocus() == Focus::PLAYER) {
        TextureManager::Instance()->draw("background", 0, 0, 1920, 1080, 1.0, m_pRenderer);
        TextureManager::Instance()->draw("borne", 300, 80, 500, 500, 1.0, m_pRenderer);
        Player::Instance()->draw(m_pRenderer);
        if (Player::Instance()->getBool())
            TextureManager::Instance()->draw("message", 748, 10, 594, 533, 0.7, m_pRenderer);
        SDL_RenderPresent(m_pRenderer); // draw to the screen
        return;
    }
    Player::Instance()->display_letters(m_pRenderer);
    Player::Instance()->adjust_letters_position();
    SDL_RenderPresent(m_pRenderer); // draw to the screen
    return;
}

void Sdl::handleInput(int value)
{
    keyPressed = NONE;
    stop_menu();
    SDL_Event ev = Sdl::getInstance()->getEvents();
    if (ev.type == SDL_KEYDOWN) {
        if(ev.key.keysym.scancode == SDL_SCANCODE_LEFT)
            keyPressed = LEFT;
        else if(ev.key.keysym.scancode == SDL_SCANCODE_RIGHT)
            keyPressed = RIGHT;
        else if(ev.key.keysym.scancode == SDL_SCANCODE_UP)
            keyPressed = UP;
        else if(ev.key.keysym.scancode == SDL_SCANCODE_DOWN)
            keyPressed = DOWN;
        else if(ev.key.keysym.scancode == SDL_SCANCODE_RETURN)
            keyPressed = ENTER;;
        SDL_Scancode tab[] = {SDL_SCANCODE_A, SDL_SCANCODE_B, SDL_SCANCODE_C, SDL_SCANCODE_D,
            SDL_SCANCODE_E, SDL_SCANCODE_F, SDL_SCANCODE_G, SDL_SCANCODE_H,
            SDL_SCANCODE_I, SDL_SCANCODE_J, SDL_SCANCODE_K, SDL_SCANCODE_L,
            SDL_SCANCODE_M, SDL_SCANCODE_N, SDL_SCANCODE_O, SDL_SCANCODE_P,
            SDL_SCANCODE_Q, SDL_SCANCODE_R, SDL_SCANCODE_S, SDL_SCANCODE_T,
            SDL_SCANCODE_U, SDL_SCANCODE_V, SDL_SCANCODE_W, SDL_SCANCODE_X,
            SDL_SCANCODE_Y, SDL_SCANCODE_Z, SDL_SCANCODE_BACKSPACE
        };
        const TrackPack tabs[27] = {TrackPack::A, TrackPack::B, TrackPack::C, TrackPack::D,
            TrackPack::E, TrackPack::F, TrackPack::G, TrackPack::H,
            TrackPack::I, TrackPack::J, TrackPack::K, TrackPack::L,
            TrackPack::M, TrackPack::N, TrackPack::O, TrackPack::P,
            TrackPack::Q, TrackPack::R, TrackPack::S, TrackPack::T,
            TrackPack::U, TrackPack::V, TrackPack::W, TrackPack::X,
            TrackPack::Y, TrackPack::Z, TrackPack::BACKSPACE
        };
        for (int i = 0; i < 26; i++) {
            if (ev.key.keysym.scancode == tab[i]) {
                keyPressed = tabs[i];
                return;
            }
        }
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
    else if (keyboard[SDL_SCANCODE_RETURN])
        keyPressed = ENTER;
    else if (keyboard[SDL_SCANCODE_DOWN])
        keyPressed =  DOWN;
    else if (keyboard[SDL_SCANCODE_LEFT])
        keyPressed =  LEFT;
    else if (keyboard[SDL_SCANCODE_RIGHT])
        keyPressed =  RIGHT;
    else if (keyboard[SDL_SCANCODE_Q]) {
        keyPressed = QUIT;
        oldState.~vector();
        SDL_DestroyWindow(m_pWindow);
        SDL_DestroyRenderer(m_pRenderer);
        SDL_Quit();
    }
    else if (keyboard[SDL_SCANCODE_L])
        keyPressed =  LIB_LEFT;
    else if (keyboard[SDL_SCANCODE_R])
        keyPressed =  LIB_RIGHT;
    else if (keyboard[SDL_SCANCODE_M])
        keyPressed =  MENU;
    else if (keyboard[SDL_SCANCODE_U])
        keyPressed =  GAME_LEFT;
    else if (keyboard[SDL_SCANCODE_D])
        keyPressed =  GAME_RIGHT;
    else if (keyboard[SDL_SCANCODE_P])
        keyPressed = PAUSE;
    else if (keyboard[SDL_SCANCODE_N])
        keyPressed =  RESTART;
    else
        keyPressed = NONE;
}

TrackPack Sdl::getEvent()
{
    return keyPressed;
}

void Sdl::init(std::vector <GameElement> configs)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        m_pWindow = SDL_CreateWindow("Nibbler", 0, 0, 1920, 1080, 0);
        m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
        SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);
    }
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
    handleInput();
    SDL_RenderClear(m_pRenderer);
    for (int i = 0; i < images.size(); i++)
        drawSprite(images[i]);
    SDL_RenderPresent(m_pRenderer);
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

void Sdl::stop_menu()
{
    if(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            SDL_DestroyWindow(m_pWindow);
            SDL_DestroyRenderer(m_pRenderer);
            SDL_Quit();
        }
    }
    return;
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

void Sdl::clean()
{
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
    return;
}

void Sdl::destroy()
{
    oldState.clear();
    for (int i = 0; i < images.size(); i++) {
        SDL_DestroyTexture(std::get<4>(images[i]));
    }
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}


extern "C" IModuleDisplay* createInstance() {
    return Sdl::getInstance();
}

extern "C" void destroyInstance(IModuleDisplay *instance) {
    //delete instance;
}