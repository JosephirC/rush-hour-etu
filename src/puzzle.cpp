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

//RULE : always min = 6, max = 13
Grid Puzzle::generateRandomGrid(int carMin, int carMax){
    
    numberOfCars = randomNumberOfCars(carMin, carMax);

    makeEmptyGrid();

    grid.displayGridId(); //test ok

    for(int i = 0; i < numberOfCars; i++){

        bool overlap = false;

        car.setPosX(randomCarsPos());
        car.setPosY(randomCarsPos());
        car.setSize(randomCarsSize());
        car.setDirection(randomCarsDirection());
        car.setId(i);

        
        vector<Car> temp = grid.getCarArray();

        if(temp.empty()){
            Car newCar(car);
            grid.addCar(newCar);
        }

        if(!temp.empty() && temp[i].getPosX() != car.getPosX() && temp[i].getPosY() != car.getPosY()){

            Car newCar(car);
            grid.addCar(newCar);
        }
    }
    
    return grid;
}