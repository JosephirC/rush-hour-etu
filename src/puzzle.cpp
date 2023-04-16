#include "puzzle.hpp"
#include <cstdlib>

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

    //grid.initEmptyGrid();
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

void Puzzle::randomCar(int x, int y, int direction, int size, int gridCarId[6][6]) { //  x=0, y=0, direction=0, size=2 par défaut
   while (gridCarId[x][y] != -1 && y<6) {
        y++;
    }
    if (gridCarId[x+1][y] != -1) {
        direction = 1;
        if (gridCarId[x][y+1] != -1) {
            std::cout << "impossible" << std::endl;
            randomCar(x+1, 0, 0, 2, gridCarId);
        }
        if (gridCarId[x][y+2] != -1) {
            size = 3;
        }
        else {
            size = 2;
        }
    }   

    car.setPosX(x);
    car.setPosY(y);
    car.setDirection(direction);
    car.setSize(size);
}

//RULE : always min = 6, max = 13
Grid Puzzle::generateRandomGrid(int carMin, int carMax){
    
    numberOfCars = randomNumberOfCars(carMin, carMax);
    std::cout << numberOfCars << std::endl;

    makeEmptyGrid();

    grid.displayGridId(); //test ok

    int gridCarId[6][6];
    grid.getGridCarId(gridCarId);

    for(int i = 0; i < numberOfCars; i++){

        bool overlap = true;


        // car.setPosX(randomCarsPos());
        // car.setPosY(randomCarsPos());
        // car.setDirection(randomCarsDirection());
        // car.setSize(randomCarsSize());
        car.setId(i);

        // for(int h = 0; h < 6; h++){
        //     for(int j = 0; j < 6; j++){
        //         cout << "  " << gridCarId[h][j] << "  ";
        //     } cout << endl;
        // }
        while (overlap) {
            if (car.getDirection() == 1) {
                if (gridCarId[car.getPosX()][car.getPosY()] == -1 && gridCarId[car.getPosX()][car.getPosY()+car.getSize()-1] == -1 && gridCarId[car.getPosX()][car.getPosY()+car.getSize()] == -1) {
                    grid.addCar(car);
                    overlap = false;

                }
            }
            else if (car.getDirection() == 0) {
                if (gridCarId[car.getPosX()][car.getPosY()] == -1 && gridCarId[car.getPosX()+car.getSize()-1][car.getPosY()] == -1 && gridCarId[car.getPosX()+car.getSize()][car.getPosY()] == -1) // vertical
                {
                    grid.addCar(car);
                    overlap = false;
                }
            }
            else {
                car.setPosX(randomCarsPos());
                car.setPosY(randomCarsPos());
                car.setSize(randomCarsSize());
                car.setDirection(randomCarsDirection());
                car.setId(i);
            }
        }

    }

    grid.displayGridId(); //test ok

    
    return grid;
}