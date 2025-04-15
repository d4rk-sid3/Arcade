/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** GameElement
*/


#ifndef GAMEELEMENT_HPP_
#define GAMEELEMENT_HPP_

#include <string>
/**
 * @class GameElement
 * @brief Une interface représentant un module de jeu
 * 
 * Cette classe représente l'ensemble des modules de jeu et fournit 
 * les méthodes communes à elles toutes pour pouvoir les utiliser
 */

class GameElement {
    private:
        std::string _value;     //< type de la valeur à stocker
        int _posx;              //< position X de la valeur à stocker
        int _posy;              //< position Y de la valeur à stocker
        char _symbol;           //< symbol représenté par l'élément
        int _size;              //< taille de l'élément à l'affichage
        std::string _sprite;    //< chemin vers le sprite de l'élément

    public:
        /**
         * @brief Constructeur de GameElement
         */
        GameElement();

        /**
         * @brief Destructeur de GameElement
         */
        ~GameElement();


        /**
         * @brief permet de set la valeur à stocker
         * 
         * @param value std::string
         */
        void setValue(std::string value);

        /**
         * @brief permet de set la valeur à stocker
         * 
         * @param value std::string
         */
        void setPosX(int posx);

        /**
         * @brief permet de set la valeur à stocker
         * 
         * @param value std::string
         */
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

#endif /* !GAMEELEMENT_HPP_ */