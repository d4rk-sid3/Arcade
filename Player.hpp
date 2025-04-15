#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <SDL2/SDL.h>
#include "TextureManager.hpp"
#include "LibDisplay/SDL/sdl.hpp"
#include "LibDisplay/SFML/sfml.hpp"
#include <vector>
#include <SFML/Graphics.h>
#include "loader.hpp"

using charValue = std::tuple<std::string, int, int>;

enum class Focus {
    NAME,
    PLAYER,
    MENU
};

class Player {
public:
    static Player* Instance() {
        if (s_pInstance == nullptr) {
            s_pInstance = new Player(960, 850, "player");
        }
        return s_pInstance;
    }
    void update(int value);
    void draw(SDL_Renderer* renderer);
    void draw(sf::RenderWindow *window, sf::Font *font);
    int getX() {return m_x;};
    int getY() {return m_y;};
    void setBool(bool value) {m_playerIsNearObject = value;};
    bool getBool(){return m_playerIsNearObject;};
    const std::vector<charValue> get_raw_inputs() const {return _raw_inputs;};
    const std::string getName() const {return _name;}
    void adjust_letters_position();
    void update_name(int value);
    void display_letters(SDL_Renderer *render);
    void display_letters(sf::RenderWindow *window, sf::Font *font);
    const Focus getFocus() {return focus;};
    void build_name();
private:
    Player(int x, int y, std::string textureID)
        : m_x(x), m_y(y), m_textureID(textureID),
          m_currentFrame(0), m_currentRow(0){}
    static Player* s_pInstance;
    std::string _name = "";
    std::vector<charValue> _raw_inputs;
    Focus focus = Focus::NAME;
    int _init_x = 850;
    int _init_y = 250;
    int m_x, m_y;
    int m_currentFrame;
    int m_currentRow;
    std::string m_textureID;
    const int m_frameWidth = 64;
    const int m_frameHeight = 64;
    const int m_frameCount = 9;
    const int m_speed = 2;
    bool m_playerIsNearObject = false;
    bool enterPressed = false;
    bool delete_letter = false;
};

#endif