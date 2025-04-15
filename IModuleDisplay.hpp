/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** IModuleDisplay
*/

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

 #ifndef IMODULEDISPLAY_HPP_
 #define IMODULEDISPLAY_HPP_
 #include <vector>
 #include <tuple>
 #include "TrackPack.hpp"
 #include "GameElement.hpp"
 
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
         virtual void init(std::vector <GameElement> configs) = 0;
 
         /**
          * @brief Gestion des entrées utilisateur
          * 
          * Gère les entrées du clavier et de la souris
          */
         virtual void handleInput() = 0;
         virtual void handleInput(int value) = 0;
         virtual void update_menu() = 0;
         virtual void init_menu() = 0;
         virtual void draw_menu() = 0;
         virtual void clean() = 0;
         virtual TrackPack getKeyPressed() = 0;
     
         /**
          * @brief Renvoie les entrées utilisateur
          * 
          * @return l'enumèration TRackpack contenant l'entrée du l'utilisateur
          */
         virtual TrackPack getEvent() = 0;
 
         virtual void update(std::vector <GameElement> configs) = 0;
     
         /**
          * @brief Affichage
          * 
          * Gère l'affichage des assets
          */
         virtual void draw() = 0;
 
         /**
          * @brief Nettoyage à la fermeture
          * 
          * Détruit les assets et libère la mémoire
          */
         virtual void stop() = 0;
 
         virtual void destroy() = 0;
 };
 
 #endif /* !IMODULEDISPLAY_HPP_ */