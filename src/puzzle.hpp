#ifndef _PUZZLE_HPP
#define _PUZZLE_HPP

#include "solver.hpp"

struct Position {
    int x;
    int y;
};

class Puzzle{
    private : 

        const int HORIZONTAL = 1;
        const int VERTICAL = 0;
        const int WIDTH = 6;
        const int HEIGHT = 6;

        Grid grid;
        Car car;

        bool rechooseNumCars;
        vector<int> allCarsSize;

    public : 

        Puzzle();

        ~Puzzle();

        //generer un nombre de voitures aleatoires entre le min et le max
        int randomNumberOfCars(int min, int max); 

        int randomCarsPos();

        int randomCarsSize();

        int randomCarsDirection();

        Grid getPuzzleGrid() const;

        void makeEmptyGrid();

        Grid generateRandomGrid(int carMin, int carMax);

        void randomGrid(int nbCars);

        void idealNumCars(int numCars);


};

#endif