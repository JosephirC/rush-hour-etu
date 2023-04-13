#include <vector>
#include <queue>
#include "solver.hpp"
#include <algorithm>
#include <iostream>

Solver::Solver(Grid* grid) {
    uncoveredGrids.push(grid);
}

void Solver::solve() {
    while (uncoveredGrids.size() > 0) {
        //verifier que chaque gridNeighbor n'a pas deja ete cover/parcouru
	    //ajouter a coveredGrid
        Grid* grid = uncoveredGrids.front();
        uncoveredGrids.pop();
        vector<Grid*> gridNeighbours = grid->getGridNeighbours();

        if(std::find(gridNeighbours.begin(), gridNeighbours.end(), grid) != gridNeighbours.end()){
            std::cout << "The grid has not been covered " << std::endl;
            coveredGrids.push_back(grid);
        }
    }
}

