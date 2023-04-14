#include <vector>
#include "grid.hpp"
#include <queue>

class Solver {
    private:

        vector<Grid*> coveredGrids;
        std::queue<Grid*> uncoveredGrids;

    public:

        Solver(Grid* grid);

        void solve1();

        void bfs();

        void solve();

        void solvedGridsSVG();

        void generateAllPossibleGrids();

        vector<Grid*> getCoveredGrids() const;

};
