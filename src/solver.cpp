#include <vector>
#include <queue>
#include "solver.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <set>

Solver::Solver(Grid* grid) {
    uncoveredGrids.push(grid);
}

bool Solver::checkContainsGrid(vector<Grid*> grid, string s) {
    for (int i=0; i<grid.size(); i++) {
        if (grid[i]->getGridString() == s)
            return true;
    }
    return false;
}

bool Solver::checkContainsGrid(std::queue<Grid*> q, string s) {
    while (!q.empty())
    {
        if (q.front()->getGridString() == s)    
            return true;
        q.pop();
    }
    return false; 
}

int Solver::isWinningGrid(Grid* grid) {
    for(int j = 0; j < grid->getCarArray().size(); j++){
        if(grid->getCarArray()[j].getId() == 0) {
            if ((grid->getCarArray()[j].getDirection() == 1 && grid->getCarArray()[j].getPosY() + grid->getCarArray()[j].getSize()-1 == grid->getExitY())
            || (grid->getCarArray()[j].getDirection() == 0 && grid->getCarArray()[j].getPosX() + grid->getCarArray()[j].getSize()-1 == grid->getExitX())) {
            
            int k = 1;

            while (grid->getParent() != nullptr) { // pour afficher en svg les étapes de résolutions
                std::string path = "./images_svg/";
                path.append(std::to_string(k));
                path.append(".svg");
                ofstream file(path);
                file << grid->svgHeader() << grid->svgRectangle() << grid->svgFooter(); 

                grid = grid->getParent();
                k++;
            }

            // on rajoute le cas initial
            std::string path = "./images_svg/";
            path.append(std::to_string(k));
            path.append(".svg");
            ofstream file(path);
            file << grid->svgHeader() << grid->svgRectangle() << grid->svgFooter(); 

            std::cout << "Gagnant en " << k-1 << " coups minimum !" <<  std::endl;
            std::cout << "-> Voir le chemin gagnant dans ../images_svg/" <<  std::endl;
            
            return k;
        }
        }
        
    }
    return -1;
}

int Solver::solve() {

    int win = -1;
    bool stop = false;

    while (uncoveredGrids.size() > 0 && win == -1 && !stop) {

        std::cout << "Number of grids covered : " << coveredGrids.size() << std::endl;
        std::cout << "Number of grids left to cover : " << uncoveredGrids.size() << std::endl;

        Grid* grid = uncoveredGrids.front();
        uncoveredGrids.pop();

        bool checkEquals = checkContainsGrid(coveredGrids, grid->getGridString()); // on vérifie si cette grille n'a pas déjà été traitée
        
        if (!checkEquals) { // si cette grille voisine n'est pas dans les grilles covered, on la rajoute dans coveredGrids
            coveredGrids.push_back(grid);
            win = isWinningGrid(grid); // on vérifie si la grille est gagnante
        }

        vector<Grid*> gridNeighbours = grid->getGridNeighbours(); // on génère tout les voisins

        for (int j=0; j<gridNeighbours.size(); j++) {
            bool checkEquals2 = checkContainsGrid(coveredGrids, gridNeighbours[j]->getGridString());
            bool checkEquals3 = checkContainsGrid(uncoveredGrids, gridNeighbours[j]->getGridString());

            if (!checkEquals2 && !checkEquals3) {
                uncoveredGrids.push(gridNeighbours[j]);
            } 
        }

        if (coveredGrids.size() > 1500) {
            stop = true;
            return -2;
        }
    }

    return win;
}

Grid* makeNewLvl(int difficulty) { // difficulty = nombre de coups à faire pour gagner ce niveau

    Grid grid(6,6);
    grid.initEmptyGrid();

    // construire une nouvelle grid avec des nouvelles positions de voitures tel que quand on appelle la fonction solve() sur cette grille, elle trouve le plus court chemin >= difficulty


}