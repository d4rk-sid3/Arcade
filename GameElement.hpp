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
};

