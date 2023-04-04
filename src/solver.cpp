#include <vector>
#include <queue>

Solver::Solver(Grid grid) {
    uncoveredGrids.push_back(grid);
}

Solver::solve() {
    while (uncoveredGrids.size > 0) {
        Grid* grid = uncoveredGrids.front();
        uncoveredGrids.pop();
        vector<Grid*> gridNeighbours = grid->getGridNeighbours();
        coveredGrids.push_back(grid);
        // verifier que chaque gridNeighbor n'a pas deja ete cover/parcouru
	    // ajouter a coveredGrid
    }
}

