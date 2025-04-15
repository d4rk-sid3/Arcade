#include "TextureManager.hpp"

TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(std::string fileName, std::string
    id, SDL_Renderer* pRenderer)
{
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
    if(pTempSurface == 0)
        return false;
    SDL_Texture* pTexture =
    SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);
    if(pTexture != 0)
    {
        m_textureMap[id] = pTexture;
        return true;
    }
    return false;
}

bool TextureManager::load(std::string fileName, std::string id, sf::RenderWindow *window)
{
    sf::Texture *texture = new sf::Texture;
    sf::Sprite *sprite = new sf::Sprite;

    if (!texture->loadFromFile(fileName))
        return false;
    sprite->setTexture(*texture);
    m_sprite_Map[id] = sprite;
    return true;
}

void TextureManager::draw(std::string id, int x, int y, int
    width, int height, float scale, SDL_Renderer* pRenderer,
    SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = width;
    srcRect.h = height;
    destRect.w = width * scale;
    destRect.h = height * scale;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,
    &destRect, 0, 0, flip);
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, sf::RenderWindow *window)
{
    m_sprite_Map[id]->setPosition(sf::Vector2f{float(x * width), float(y * height)});
    window->draw(*m_sprite_Map[id]);
    return;
}

SDL_Texture* TextureManager::getTexture(const std::string& id)
{
    return m_textureMap[id];
}