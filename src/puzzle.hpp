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

        // Taxi (Winning Car)
        int taxiPosX; 
        int taxiPosY;
        int taxiSize;
        int taxiDirection;

        int exitPosX;
        int exitPosY;

        int numberOfCars;
        int carsPosX;
        int carsPosY;
        int carsSize;
        int carsDirection;
        //int exitDirection;
        bool isSolvable;
        vector<string> freePositions;
        Grid grid;
        Car car;

    public : 

        Puzzle();

        ~Puzzle();

        //generer un nombre de voitures aleatoires entre le min et le max (ca aide pour faire des niveaux dans sdl)
        int randomNumberOfCars(int min, int max); 

        int randomCarsPos();

        int randomCarsSize();

        int randomCarsDirection();

        void taxiExit();

        void setNumberOfCars(int s);

        Grid getPuzzleGrid() const;

        void makeEmptyGrid();

        void randCar(int gridCarId[6][6]);

        void randCar2(int gridCarId[6][6]);

        Grid generateRandomGrid(int carMin, int carMax);

        Grid generateRandomPuzzle();

        int randomCar(int gridCarId[6][6]);

        int randomGrid(int nbCars);

};

#endif