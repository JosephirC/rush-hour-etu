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

        void solvedGridsSVG(Grid* grid, string filenumber);

        bool checkContainsGrid(vector<Grid*> grid, string s);

        bool checkContainsGrid(std::queue<Grid*> q, string s);

        vector<Grid*> getCoveredGrids() const;

        void solveALL();

        void solveTest();

        int isWinningGrid(Grid* grid);

        vector<Grid*> getWinningGrids();

        void puzzle();

};

#endif
