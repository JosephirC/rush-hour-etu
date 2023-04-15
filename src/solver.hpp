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

        void solvedGridsSVG();

        bool checkContainsGrid(vector<Grid*> grid, string s);

        bool checkContainsGrid(std::queue<Grid*> q, string s);

        vector<Grid*> getCoveredGrids() const;

        void solveALL();

};
