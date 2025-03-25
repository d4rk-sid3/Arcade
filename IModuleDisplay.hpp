/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** IModuleDisplay
*/

#ifndef IMODULEDISPLAY_HPP_
#define IMODULEDISPLAY_HPP_

/**
 * @file IModuleDisplay.hpp
 * @brief Définition de la classe IDisplayModule
 * 
 * Ce fichier contient la définition de la classe IDisplayModule, 
 * qui est une interface permettent de gérer les modules d'affichages
 * 
 * @author Oscar Gbenou
 * @date 25 Mars 2025
 */



/**
 * @class IModuleDisplay 
 * @brief Une interface représentant un module d'affichage
 * 
 * Cette classe représente l'ensemble des modules graphiques et fournit 
 * les méthodes communes à elles toutes pour pouvoir les utiliser
 */

class IModuleDisplay {
    public:
        /**
        * @brief Destructeur par défaut.
        * 
        * Destructeur virtuel pour éviter les fuites mémoire
        */
        virtual ~IModuleDisplay() = default;

        /**
         * @brief Initialisation
         * 
         * Initialise les données de base du modules
         */
        virtual void init() = 0;

        /**
         * @brief Affichage
         * 
         * Gère l'affichage des assets
         */
        virtual void render() = 0;

        /**
         * @brief Gestion des entrées utilisateur
         * 
         * Gère les entrées du clavier et de la souris
         */
        virtual void handleInput() = 0;

        /**
         * @brief Nettoyage à la fermeture
         * 
         * Détruit les assets et libère la mémoire
         */
        virtual void shutdown() = 0;
};

#endif /* !IMODULEDISPLAY_HPP_ */
