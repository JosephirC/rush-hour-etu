#include <vector>
#include "grid.hpp"
#include <queue>

class Solver {
    private:

        vector<Grid*> coveredGrids;
        std::queue<Grid*> uncoveredGrids;

    public:

        Solver(Grid* grid);

        void solve();

        void solvedGridsSVG(Grid* grid, string filenumber);

        vector<Grid*> getCoveredGrids() const;

        void solveALL();

        void solveTest();

        bool isWinningGrid(Grid* grid);

        vector<Grid*> getWinningGrids();

        void puzzle();

};
