/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** sfml
*/

#ifndef SFML_HPP_
#define SFML_HPP_
    #include <SFML/Graphics.hpp>
    #include <iostream>
    #include "IModuleDisplay.hpp"

    class Sfml : public IModuleDisplay {
        public:
            Sfml();
            ~Sfml();
            void init(std::vector <GameElement> configs) override;
            void handleInput() override;
            TrackPack getEvent() override;
            void draw() override;
            void update() override;
            void stop() override;
        private:
            TrackPack keyPressed;
    };

#endif /* !SFML_HPP_ */
