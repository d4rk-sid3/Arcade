/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** GameElement
*/

#include "GameElement.hpp"

GameElement::GameElement()
{
}

GameElement::~GameElement()
{
}

void GameElement::setValue(std::string value)
{
    _value = value;
}

void GameElement::setPosX(int posx)
{
    _posx = posx;
}

void GameElement::setPosY(int posy)
{
    _posy = posy;
}

void GameElement::setSymbol(char sym)
{
    _symbol = sym;
}

void GameElement::setSpriteSize(int size)
{
    _size = size;
}

void GameElement::setSprite(std::string sprite){
    _sprite = sprite;
}

std::string GameElement::getValue() const
{
    return _value;
}

int GameElement::getPosX() const
{
    return _posx;
}

int GameElement::getPosY() const
{
    return _posy;
}

char GameElement::getSymbol() const
{
    return _symbol;
}

int GameElement::getSpriteSize() const
{
    return _size;
}

std::string GameElement::getSprite() const
{
    return _sprite;
}

bool GameElement::operator== (GameElement &tmp) {
    return ((this->getValue() == tmp.getValue()) && (this->getPosX() == tmp.getPosX()) && (this->getPosY() == tmp.getPosY()) && (this->getSymbol() == tmp.getSymbol()));
};