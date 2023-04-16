#ifndef _PUZZLE_HPP
#define _PUZZLE_HPP

#include "solver.hpp"

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

        Grid getPuzzleGrid() const;

        void makeEmptyGrid();

        int randCar(int &gridCarId[6][6]);

        Grid generateRandomGrid(int carMin, int carMax);

        Grid generateRandomPuzzle();
        void randomCar(int x, int y, int direction, int size, int gridCarId[6][6]);

};

#endif