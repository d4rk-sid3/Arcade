/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** GameElement
*/

/**
 * @class GameElement
 * @brief Une interface représentant un module de jeu
 * 
 * Cette classe représente l'ensemble des modules de jeu et fournit 
 * les méthodes communes à elles toutes pour pouvoir les utiliser
 */

#ifndef GAMEELEMENT_HPP_
#define GAMEELEMENT_HPP_

#include <string>

class GameElement {
    private:
        std::string _value;
        int _posx;
        int _posy;
        char _symbol;
        int _size;
        std::string _sprite;

    public:
        GameElement();
        ~GameElement();
        void setValue(std::string value);
        void setPosX(int posx);
        void setPosY(int posy);
        void setSymbol(char sym);
        void setSpriteSize(int size);
        void setSprite(std::string sprite);
        std::string getValue() const;
        int getPosX() const;
        int getPosY() const;
        char getSymbol() const;
        int getSpriteSize() const;
        std::string getSprite() const;
        bool operator== (GameElement &tmp);
        GameElement *operator= (GameElement &tmp) {
            this->_posx = tmp.getPosX();
            this->_posy = tmp.getPosY();
            this->_symbol = tmp.getSymbol();
            this->_size = tmp.getSpriteSize();
            this->_sprite = tmp.getSprite();
            return this;
        }
};
extern int current_a;
extern int current_b;
#endif /* !GAMEELEMENT_HPP_ */