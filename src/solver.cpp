#include <vector>
#include <queue>
#include "solver.hpp"

Solver::Solver(Grid* grid) {
    uncoveredGrids.push(grid);
}

void Solver::solve() {
    while (uncoveredGrids.size() > 0) {
        Grid* grid = uncoveredGrids.front();
        uncoveredGrids.pop();
        vector<Grid*> gridNeighbours = grid->getGridNeighbours();
        coveredGrids.push_back(grid);
        // verifier que chaque gridNeighbor n'a pas deja ete cover/parcouru
	    // ajouter a coveredGrid
    }
}

