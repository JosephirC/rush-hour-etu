#ifndef _SOLVER_HPP
#define _SOLVER_HPP

#include <vector>
#include "grid.hpp"
#include <queue>

class Solver {
    private:

        vector<Grid*> coveredGrids; // liste des grilles déjà traitées par le parcours en largeur
        std::queue<Grid*> uncoveredGrids; // liste des grilles restantes à traiter

    public:
        /** @brief Destructeur de Grid 
         *  @param grid : grille à résoudre
        */
        Solver(Grid* grid);

        /** @brief vérifie si une grille (donnée en paramètre sous forme de string) est présente dans un vecteur de grilles
         *  @param grid : vecteur de grilles
         *  @param s : grille sous forme de string
         *  @return true si la grille est présente dans le vecteur de grilles
        */
        bool checkContainsGrid(vector<Grid*> grid, string s);

        /** @brief vérifie si une grille (donnée en paramètre sous forme de string) est présente dans une queue de grilles
         *  @param grid : queue de grilles
         *  @param s : grille sous forme de string
         *  @return true si la grille est présente dans la queue de grilles
        */
        bool checkContainsGrid(std::queue<Grid*> q, string s);

        /** @brief vérifie si une grille est gagnante ou pas
         *  @param grid : pointeur vers une grille
         *  @return le nombre de coups pour résoudre la grille (ou -1 si la grille n'a pas de solution)
        */
        int isWinningGrid(Grid* grid);
        
        /** @brief Fonction qui résout la grille
         *  @return Un entier qui représente le nombre de coups pour résoudre la grille (ou -1 si la grille n'a pas de solution, -2 si on arrete la grille manuellement)
        */
        int solve();
};

#endif
