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

        vector<Grid*> getCoveredGrids() const;

};
