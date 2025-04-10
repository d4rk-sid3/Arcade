/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** GameElement
*/

/**
 * @file GameElement.hpp
 * @brief Définition de la classe IDisplayGame
 * 
 * Ce fichier contient la définition de la classe IDisplayGame, 
 * qui est une interface permettent de gérer les modules de jeu
 * 
 * @author Oscar Gbenou
 * @date 25 Mars 2025
 */

/**
 * @class GameElement
 * @brief Une interface représentant un module de jeu
 * 
 * Cette classe représente l'ensemble des modules de jeu et fournit 
 * les méthodes communes à elles toutes pour pouvoir les utiliser
 */

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
        GameElement() {};
        ~GameElement() {};
        void setValue(std::string value) {_value = value;};
        void setPosX(int posx) {_posx = posx;};
        void setPosY(int posy) {_posy = posy;};
        void setSymbol(char sym) {_symbol = sym;};
        void setSpriteSize(int size) {_size = size;};
        void setSprite(std::string sprite) {_sprite = sprite;};
        std::string getValue() const {return _value;};
        int getPosX() const {return _posx;};
        int getPosY() const {return _posy;};
        char getSymbol() const {return _symbol;};
        int getSpriteSize() const {return _size;};
        std::string getSprite() const {return _sprite;};
        bool operator== (GameElement &tmp) {
            return ((this->getValue() == tmp.getValue()) && (this->getPosX() == tmp.getPosX()) && (this->getPosY() == tmp.getPosY()) && (this->getSymbol() == tmp.getSymbol()));
        };
};

