#include "Player.hpp"

Player* Player::s_pInstance = 0;

void Player::update_name(int value)
{
    IModuleDisplay *input;
    DLLoader<Sfml> sfml("./lib/arcade_sfml.so");
    DLLoader<Sdl> sdl("./lib/arcade_sdl2.so");

    if (value == 0)
        input = sdl.getInstance();
    else if (value == 1)
        input = sfml.getInstance();
    input->handleInput(1);
    TrackPack _value = input->getKeyPressed();
    delete_letter = false;

    const TrackPack TrackPacks[26] = {TrackPack::A, TrackPack::B, TrackPack::C, TrackPack::D,
        TrackPack::E, TrackPack::F, TrackPack::G, TrackPack::H,
        TrackPack::I, TrackPack::J, TrackPack::K, TrackPack::L,
        TrackPack::M, TrackPack::N, TrackPack::O, TrackPack::P,
        TrackPack::Q, TrackPack::R, TrackPack::S, TrackPack::T,
        TrackPack::U, TrackPack::V, TrackPack::W, TrackPack::X,
        TrackPack::Y, TrackPack::Z
    };
    const char* letters[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p",
        "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    for (size_t i = 0; i < 26; i++) {
        if (_value == TrackPacks[i]) {
            _raw_inputs.push_back(std::make_tuple(letters[i], _init_x, _init_y));
            _init_x += 20;
            return;
        }
    }
    if (_value == BACKSPACE && _raw_inputs.size() > 0) {
        _raw_inputs.pop_back();
        delete_letter = true;
    }
    if (_value == ENTER) {
        focus = Focus::PLAYER;
        build_name();
    }
    return;
}

void Player::build_name()
{
    std::string name = "";

    for (int i = 0; i < _raw_inputs.size(); i++)
        name += std::get<0>(_raw_inputs[i]);
    _name = name;
    return;
}

void Player::adjust_letters_position()
{
    if (delete_letter)
        _init_x -= 20;
    if (_init_x < 0)
        _init_x = 300;
    return;
}

void Player::display_letters(SDL_Renderer *render)
{
    SDL_Color titleColor = {255, 255, 255, 255};
    SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
    SDL_RenderClear(render);

    TextRenderer::Instance()->drawText("Enter your name : ", 850, 200, titleColor, render);
    SDL_Rect textRect = {1650, 900, 200, 50};
    SDL_SetRenderDrawColor(render, 32, 64, 114, 255); // Bleu
    SDL_RenderFillRect(render, &textRect);
    TextRenderer::Instance()->drawText("VALIDER", 1700, 910, titleColor, render);
    for (int i = 0; i < _raw_inputs.size(); i++) {
        std::string text = std::get<0>(_raw_inputs[i]);
        int x = std::get<1>(_raw_inputs[i]);
        int y = std::get<2>(_raw_inputs[i]);
        TextRenderer::Instance()->drawText(text, x, y, titleColor, render);
    }
    if (focus == Focus::PLAYER) {
        SDL_Rect textRect = {1650, 900, 200, 50};
        SDL_SetRenderDrawColor(render, 255, 0, 0, 0); // Rouge
        SDL_RenderFillRect(render, &textRect);
        TextRenderer::Instance()->drawText("VALIDER", 1700, 910, titleColor, render);
    }
}

void Player::display_letters(sf::RenderWindow *window, sf::Font *font)
{
    window->clear();
    TextRenderer::Instance()->drawText("Enter your name : ", 850, 200, sf::Color::White, font, window);
    TextRenderer::Instance()->drawText("VALIDER", 1700, 910, sf::Color::White, font, window);
    sf::RectangleShape textRect(sf::Vector2f{200, 50});

    textRect.setPosition(sf::Vector2f{1650, 900});
    for (int i = 0; i < _raw_inputs.size(); i++) {
        std::string text = std::get<0>(_raw_inputs[i]);
        int x = std::get<1>(_raw_inputs[i]);
        int y = std::get<2>(_raw_inputs[i]);
        TextRenderer::Instance()->drawText(text, x, y, sf::Color::White, font, window);
    }
    return;
}

void Player::update(int value) 
{
    IModuleDisplay *input;
    DLLoader<Sfml> sfml("./lib/arcade_sfml.so");
    DLLoader<Sdl> sdl("./lib/arcade_sdl2.so");

    if (value == 0)
        input = sdl.getInstance();
    else if (value == 1)
        input = sfml.getInstance();
    input->handleInput();
    enterPressed = false;

    bool moving = false;
    TrackPack _value = input->getKeyPressed();

    if (_value == UP) {
        m_y -= m_speed;
        m_currentRow = 0;
        moving = true;
    } else if (_value == DOWN) {
        m_y += m_speed;
        m_currentRow = 2;
        moving = true;
    } else if (_value == LEFT) {
        m_x -= m_speed;
        m_currentRow = 1;
        moving = true;
    } else if (_value == RIGHT) {
        m_x += m_speed;
        m_currentRow = 3;
        moving = true;
    }
    else if (_value == ENTER)
        enterPressed = true;
    if (moving)
        m_currentFrame = (SDL_GetTicks() / 100) % m_frameCount;
    else
        m_currentFrame = 0;
    int objX = 520;
    int objY = 256;
    int minDistance = 200;
    int dx = m_x - objX;
    int dy = m_y - objY;
    float distance = std::sqrt(dx * dx + dy * dy);
    setBool(distance < minDistance);
    if (m_playerIsNearObject && enterPressed)
        focus = Focus::MENU;
    return;
}

void Player::draw(SDL_Renderer* renderer)
{
    SDL_Rect srcRect = {
        m_currentFrame * m_frameWidth,
        m_currentRow * m_frameHeight,
        m_frameWidth,
        m_frameHeight
    };
    SDL_Rect destRect = {
        m_x,
        m_y,
        m_frameWidth * 2,
        m_frameHeight * 2
    };
    SDL_Color titleColor = {0, 0, 0, 0}; //Noir
    SDL_RenderCopy(renderer, TextureManager::Instance()->getTexture(m_textureID), &srcRect, &destRect);
    SDL_Rect textRect = {m_x - 10, m_y - 10, 170, 30};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Blanc
    SDL_RenderFillRect(renderer, &textRect);
    TextRenderer::Instance()->drawText(_name, m_x + 10, m_y - 10, titleColor, renderer);
}

void Player::draw(sf::RenderWindow *window, sf::Font *font)
{
    TextureManager::Instance()->getSprite(m_textureID)->setTextureRect(sf::IntRect(
        m_currentFrame * m_frameWidth,
        m_currentRow * m_frameHeight,
        m_frameWidth,
        m_frameHeight
    ));
    TextureManager::Instance()->getSprite(m_textureID)->setPosition(static_cast<float>(m_x), static_cast<float>(m_y));
    TextureManager::Instance()->getSprite(m_textureID)->setScale(2.0f, 2.0f);
    window->draw(*TextureManager::Instance()->getSprite(m_textureID));
    TextRenderer::Instance()->drawText(_name, m_x + 10, m_y - 10, sf::Color::White, font, window);
    return;
}