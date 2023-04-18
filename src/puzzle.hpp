#ifndef _PUZZLE_HPP
#define _PUZZLE_HPP

#include "solver.hpp"

struct Position {
    int x;
    int y;
};

class Puzzle{
    private : 

        const int HORIZONTAL = 1;
        const int VERTICAL = 0;
        const int WIDTH = 6;
        const int HEIGHT = 6;

        Grid grid; // grille qui va etre modifiée puis retournée quand valide
        Car car; // voiture "tempon" pour push différentes voitures dans la grid

    public : 
        /** @brief Constructeur de Puzzle 
        */
        Puzzle();

        /** @brief Destructeur de Puzzle 
        */
        ~Puzzle();

        /** @brief Génère un nombre aléatoire compris entre min et max
         *  @param min : minimum de voitures à générer 
         *  @param max : maximum de voitures à générer 
         *  @return : un nombre aléatoire compris entre min et max
        */
        int randomNumberOfCars(int min, int max);

        /** @brief Génère une position aléatoire de voiture
         *  @return : un nombre aléatoire compris entre 0 et 5
        */
        int randomCarsPos();

        /** @brief Génère une taille aléatoire de voiture
         *  @return : un nombre aléatoire compris entre 2 et 3
        */
        int randomCarsSize();

        /** @brief Génère une direction aléatoire de voiture
         *  @return : un nombre aléatoire compris entre 0 et 1
        */
        int randomCarsDirection();

        /** @brief Retourne la grille du puzzle
         *  @return : la grille du puzzle
        */
        Grid getPuzzleGrid() const;

        /** @brief Initialise une grille vide
        */
        void makeEmptyGrid();

        /** @brief Fonction qui va appeler la fonction randomGrid pour générer une grille random
        /** @param carMin : nombre minimum de voitures
        /** @param carMax : nombre maximum de voitures
        /** @return La grille random génerée
        */
        Grid generateRandomGrid(int carMin, int carMax);

        /** @brief Génère une grille random avec un nombre de voitures compris entre carMin et carMax
         *  @param nbCars : nombre de voitures dans la grille à générer
        */
        void randomGrid(int nbCars);

};

#endif