#ifndef _SOLVER_HPP
#define _SOLVER_HPP

#include <vector>
#include "grid.hpp"
#include <queue>

class Solver {
    private:

        vector<Grid*> coveredGrids;
        std::queue<Grid*> uncoveredGrids;

    public:

        Solver(Grid* grid);

        int solve();

        bool checkContainsGrid(vector<Grid*> grid, string s);

        bool checkContainsGrid(std::queue<Grid*> q, string s);

        int isWinningGrid(Grid* grid);
};

#endif
