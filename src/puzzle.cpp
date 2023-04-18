#include "puzzle.hpp"
#include <cstdlib>
#include <algorithm>
#include <ctime>

Puzzle::Puzzle(){
<<<<<<< HEAD
    rechooseNumCars = false;
=======
>>>>>>> 7289a3cb6e38f4cd25477d34893cd7d98f2701dc
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
            allCarsSize.push_back(size);
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
                            grid.setExitPosX(HEIGHT - 1);
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
<<<<<<< HEAD
                            grid.setExitPosY(WIDTH - 1);
=======
                            grid.setExitPosY(5);
>>>>>>> 7289a3cb6e38f4cd25477d34893cd7d98f2701dc
                        }

                        break;
                    }
                }
            }
        }
    }
}

void Puzzle::idealNumCars(int numCars){

    int gridSize = WIDTH * HEIGHT;
    int gridCapacity = gridSize + 3;
    int numGridCars = std::ceil(gridCapacity / 3);

    cout << "numcars : " << numCars << ", numgridCars : " << numGridCars << endl;

    if(numCars > numGridCars){
        std::cout << "Hard to fit " << numCars << " in a " << gridSize << " gridd.." << endl;
        std::cout << "Please choose a number of cars between " <<  numGridCars - 4 << " and " << numGridCars << endl; 
        rechooseNumCars = true;
    }

    int occupiedGridSize = 0;

    for(int i = 0; i < allCarsSize.size(); i++){
        occupiedGridSize += allCarsSize[i];
    }

}

// pas plus de 13 voitures dans la grille, ou ça devient impossible de toutes les faire rentrer sinon
Grid Puzzle::generateRandomGrid(int carMin, int carMax){
    
    int numberOfCars = randomNumberOfCars(carMin, carMax);

    idealNumCars(numberOfCars);

    if(rechooseNumCars){
        rechooseNumCars = false;
        generateRandomGrid(carMin, carMax);
    }

    makeEmptyGrid();

    randomGrid(numberOfCars);

    return grid;
}