/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** IModuleGame
*/

/**
 * @file IModuleGame.hpp
 * @brief Définition de la classe IDisplayGame
 * 
 * Ce fichier contient la définition de la classe IDisplayGame, 
 * qui est une interface permettent de gérer les modules de jeu
 * 
 * @author Oscar Gbenou
 * @date 25 Mars 2025
 */

#ifndef IMODULEGAME_HPP_
#define IMODULEGAME_HPP_

#include <vector>
#include "GameElement.hpp"
#include "TrackPack.hpp"
#include <ctime>

/**
 * @enum state
 * @brief Describe the different kind of init
 */

enum state {
    REST, //< When we want to restart
    SAVE, //< When we want to start by a save
    OVER //< When we want to display the over screen
};

/**
 * @interface IGameModule
 * @brief Une interface représentant un module de jeu
 * 
 * Cette classe représente l'ensemble des modules de jeu et fournit 
 * les méthodes communes à elles toutes pour pouvoir les utiliser
 */

class IGameModule {
    public:
        /**
        * @brief Destructeur par défaut.
        * 
        * Destructeur virtuel pour éviter les fuites mémoire
        */
        ~IGameModule() = default;

        /**
         * @brief Initialisation les objets
         * 
         * Créer les élémnts nécessaires à la réalisation du jeu
         */
        virtual void init(state check) = 0;

        /**
         * @brief Mise à jour des objets du jeu
         * 
         * Actualise l'état du jeu
         */
        virtual void update() = 0;

        /**
         * @brief Récupère les entrées de l'utlisateur
         * 
         * Actualise les paramètres du jeu
         * 
         * @param keyCode Entrée de l'utilisateur
         * @see TrackPack
         */
        virtual void handleInput(TrackPack keyCode) = 0;

        /**
         * @brief Renvoie l'état du jeu
         * 
         * @return Un tableau contanant chaque élément constituant le jeu
         */
        virtual std::vector <GameElement> getGameState() const = 0;


        /**
         * @brief Renvoie le score du joueur
         * 
         * @return Les points marqués par le joueur
         */
        virtual int getScore() const = 0;


        /**
         * @brief Renvoie si le jeu est terminé ou pas
         * 
         * @return Vrai si le jeu est terminé Faux dans le cas contraire
         */
        virtual bool isGameOver() const = 0;


        /**
         * @brief met le jeu en pause
         */
        virtual void setpaused() = 0;


        /**
         * @brief Detruit les différentes vraibles inportantes du jeu
         */
        virtual void destroy() = 0;
};

#endif /* !IMODULEGAME_HPP_ */
