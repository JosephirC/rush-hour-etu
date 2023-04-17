#include "puzzle.hpp"
#include <cstdlib>
#include <algorithm>
#include <ctime>

Puzzle::Puzzle(){

    taxiPosX = 0;
    taxiPosY = 0;
    taxiSize = 0;
    taxiDirection = 0;

    exitPosX = 0;
    exitPosY = 0;

    numberOfCars = 0;
    carsSize = 0;
    carsDirection = 0;
    isSolvable = false;

    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            std::string str_i = std::to_string(i);
            std::string str_j = std::to_string(j);
            std::string s = str_i + str_j;
            freePositions.push_back(s);
        }
    }

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

void Puzzle::taxiExit(){
    
    int randomSide = rand() % 2;

    if(taxiDirection == HORIZONTAL){
        if(randomSide == 0){ // Exit left
            exitPosX = taxiPosX;
            exitPosY = 0;
        }
        else{ // Exit right
            exitPosX = taxiPosX;
            exitPosY = taxiPosY + (WIDTH - taxiPosY - 1); 
        }
    }

    if(taxiDirection == VERTICAL){
        if(randomSide == 0){ // Exit up
            exitPosX = 0;
            exitPosY = taxiPosY;
        }
        else{ //Exit down 
            exitPosX = taxiPosX + (VERTICAL - taxiPosX - 1);
            exitPosY = taxiPosY;
        }
    }
}

Grid Puzzle::getPuzzleGrid() const{
    return grid;
}

void Puzzle::makeEmptyGrid(){
    grid.setWidth(WIDTH);
    grid.setHeight(HEIGHT);
    grid.setExitPosX(exitPosX);
    grid.setExitPosY(exitPosY);
    grid.setParent(nullptr);
    grid.setGridString(" ");
    grid.initEmptyGrid();

    vector<Car> c;
    grid.setCarArray(c);

}

int Puzzle::randomGrid(int nbCars) {

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

//RULE : always min = 6, max = 13
Grid Puzzle::generateRandomGrid(int carMin, int carMax){
    
    numberOfCars = randomNumberOfCars(carMin, carMax);

    makeEmptyGrid();

    randomGrid(numberOfCars);

    return grid;
}