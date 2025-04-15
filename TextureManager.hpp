#ifndef __Texture__
#define __Texture__
#include <iostream>
#include <memory.h>
#include <map>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SFML/Graphics.hpp>

class TextureManager {
    private:
        std::map<std::string, SDL_Texture*> m_textureMap;
        std::map<std::string, sf::Sprite *> m_sprite_Map;
        static TextureManager* s_pInstance;
        TextureManager(){};
    public:
        ~TextureManager(){};
        static TextureManager* Instance() {
            if (s_pInstance == nullptr) {
                s_pInstance = new TextureManager();
            }
            return s_pInstance;
        }
        bool load(std::string fileName,std::string id,
        SDL_Renderer* pRenderer);
        bool load(std::string fileName, std::string id, sf::RenderWindow *window);
        void draw(std::string id, int x, int y, int width, int
        height, float scale, SDL_Renderer* pRenderer, SDL_RendererFlip flip =
        SDL_FLIP_NONE);
        void draw(std::string id, int x, int y, int width, int height, sf::RenderWindow *window);
        SDL_Texture* getTexture(const std::string& id);
        sf::Sprite *getSprite(const std::string &id) {return m_sprite_Map[id];};     
};
#endif /* defined(__Game__) */