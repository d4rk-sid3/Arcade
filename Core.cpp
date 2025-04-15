#include "Core.hpp"

Core::Core(std::vector <IGameModule*> _all_games, std::vector <IModuleDisplay*> _all_display,
    int _game, int _lib) : all_display(_all_display), all_games(_all_games),
    current_game(_game), current_display(_lib)
{
    menu = Menu::Instance();
}

Core::~Core()
{
}

void Core::destroyall()
{
    all_games[current_game]->destroy();
    for (int i = 0; i < all_games.size(); i++) {
        delete all_games[i];
    }
    all_display[current_display]->destroy();
    for (int i = 0; i < all_display.size(); i++) {
        delete all_display[i];
    }
}

update_return Core::update(TrackPack keyCode)
{
    if (keyCode == UP)
        return LOGIQUE;
    else if (keyCode == DOWN)
        return LOGIQUE;
    else if (keyCode == LEFT)
        return LOGIQUE;
    else if (keyCode == RIGHT)
        return LOGIQUE;
    else if (keyCode == QUIT) {
        destroyall();
        return QUITALL;
    } else if (keyCode == LIB_LEFT) {
        all_games[current_game]->setpaused();
        all_display[current_display]->destroy();
        current_display -= 1;
        return DISPLAY;
    } else if (keyCode == LIB_RIGHT) {
        all_games[current_game]->setpaused();
        all_display[current_display]->destroy();
        current_display += 1;
        return DISPLAY;
    } else if (keyCode == MENU)
        return CONFIG;
    else if (keyCode == GAME_LEFT) {
        all_games[current_game]->destroy();
        current_game -= 1;
        return GAME;
    } else if (keyCode == GAME_RIGHT) {
        all_games[current_game]->destroy();
        current_game += 1;
        return GAME;
    } else if (keyCode == PAUSE)
        return CONFIG;
    else if (keyCode == RESTART)
        return CONFIG;
    else if (keyCode == NONE)
        return LOGIQUE;
    return EMPTY;
}

void Core::runGame(TrackPack keycode)
{
    bool isquited = false;
    all_games[current_game]->init(SAVE);
    all_display[current_display]->init(all_games[current_game]->getGameState());
    int a = 0;
    while (!isquited) {
        all_display[current_display]->handleInput();
        keycode = all_display[current_display]->getEvent();
        update_return check;
        
        check = update(keycode);
        if (check == LOGIQUE) {
            all_games[current_game]->handleInput(keycode);
            all_games[current_game]->update();
            all_display[current_display]->update(all_games[current_game]->getGameState());
            all_display[current_display]->draw();
        }
        if (check == DISPLAY) {
            if (current_display < 0)
                current_display = 2;
            else if (current_display > 2)
                current_display = 0;
            all_games[current_game]->setpaused();
            all_display[current_display]->init(all_games[current_game]->getGameState());
        }
        if (check == QUITALL) {
            isquited = true;
            break;
        }
        if (check == CONFIG) {
            if (keycode == PAUSE) {
                all_games[current_game]->setpaused();
            }
            if (keycode == RESTART) {
                all_games[current_game]->destroy();
                all_games[current_game]->init(REST);
            }
        }
        if (check == GAME) {
             if (current_game < 0)
                current_game = 1;
            else if (current_game > 1)
                current_game = 0;
            all_games[current_game]->init(SAVE);
        }
        if (all_games[current_game]->isGameOver()) {
            all_games[current_game]->destroy();
            all_games[current_game]->init(OVER);
        }
    }
}

void Core::runMenu(int value)
{
    bool isquitted = false;
    IModuleDisplay *display = all_display[value];
    display->init_menu();

    while (!isquitted) {
        display->update_menu();
        if (display->getKeyPressed() == QUIT) {
            isquitted = true;
            break;
        }
        display->draw_menu();
        SDL_Delay(10);
    }
    display->clean();
    return;
}