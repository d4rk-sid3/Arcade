/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** IModuleGame
*/

#ifndef IMODULEGAME_HPP_
#define IMODULEGAME_HPP_

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



/**
 * @class IModuleGame
 * @brief Une interface représentant un module de jeu
 * 
 * Cette classe représente l'ensemble des modules de jeu et fournit 
 * les méthodes communes à elles toutes pour pouvoir les utiliser
 */

class IModuleGame {
    public:
        /**
        * @brief Destructeur par défaut.
        * 
        * Destructeur virtuel pour éviter les fuites mémoire
        */
        ~IModuleGame() = default;

        /**
         * @brief Initialisation
         * 
         * Initialise les données de base du module
         */
        virtual void init() = 0;

        /**
         * @brief Mise à jour des objets du jeu
         * 
         * Récupère les changement et les applique au objets
         */
        virtual void update() = 0;


        /**
         * @brief Vérifivation de l'état du jeu
         * @return L'etat du jeu
         * 
         * Vérifie si le jeu est terminer ou pas
         */
        virtual bool is_running() = 0;

        /**
         * @brief Destruction des objets créer
         * 
         * Détruit les assets et libère la mémoire
         */
        virtual void destroyer() = 0;
};

#endif /* !IMODULEGAME_HPP_ */
