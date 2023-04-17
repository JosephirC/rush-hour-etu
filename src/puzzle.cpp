#include "puzzle.hpp"
#include <cstdlib>
#include <algorithm>
#include <ctime>

Puzzle::Puzzle(){
}

Puzzle::~Puzzle(){

}

int Puzzle::randomNumberOfCars(int min, int max){
    return rand() % (max - min + 1) + min;
}

int Puzzle::randomCarsDirection(){
    return rand() % 2;
}

int Puzzle::randomCarsSize(){
    return rand() % 2 + 2;
}

int Puzzle::randomCarsPos(){
    return rand() % 6;
}

Grid Puzzle::getPuzzleGrid() const{
    return grid;
}

void Puzzle::makeEmptyGrid(){
    grid.setWidth(WIDTH);
    grid.setHeight(HEIGHT);
    grid.setExitPosX(0);
    grid.setExitPosY(0);
    grid.setParent(nullptr);
    grid.setGridString(" ");
    grid.initEmptyGrid();
    vector<Car> c;
    grid.setCarArray(c);

}

void Puzzle::randomGrid(int nbCars) {

    srand(time(0));

    int gridTest[6][6];

    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            gridTest[i][j] = -1;
        }
    }

    for (int i=0; i<nbCars; i++) {

        while (true) {

            int direction = randomCarsDirection();
            int size = randomCarsSize();
            int x = randomCarsPos();
            int y = randomCarsPos();

            bool overlapping = false;

            if (direction == 0) { // vertical
                if (x+size <6) {
                    for (int j=x; j<x+size; j++) {
                        if (gridTest[j][y] != -1) {
                            overlapping = true;
                            break;
                        }
                    }

                    if (!overlapping) {
                        for (int j=x; j<x+size; j++) {
                            gridTest[j][y] = i;
                        }
                        car.setPosX(x);
                        car.setPosY(y);
                        car.setDirection(direction);
                        car.setSize(size);
                        car.setId(i);
                        grid.addCar(car);
                        if (i==0) {
                            grid.setExitPosX(5);
                            grid.setExitPosY(y);
                        }
                        
                        break;
                    }
                }
                
            }
            else if (direction == 1) { // horizontal
                if (y+size <6) {
                    for (int j=y; j<y+size; j++) {
                        if (gridTest[x][j] != -1) {
                            overlapping = true;
                            break;
                        }
                    }

                    if (!overlapping) {
                        for (int j=y; j<y+size; j++) {
                            gridTest[x][j] = i;
                        }
                        car.setPosX(x);
                        car.setPosY(y);
                        car.setDirection(direction);
                        car.setSize(size);
                        car.setId(i);
                        grid.addCar(car);                        
                        if (i==0) {
                            grid.setExitPosX(x);
                            grid.setExitPosY(5);
                        }

                        break;
                    }
                }
            }
        }
    }
}

// pas plus de 13 voitures dans la grille, ou ça devient impossible de toutes les faire rentrer sinon
Grid Puzzle::generateRandomGrid(int carMin, int carMax){
    
    int numberOfCars = randomNumberOfCars(carMin, carMax);

    makeEmptyGrid();

    randomGrid(numberOfCars);

    return grid;
}