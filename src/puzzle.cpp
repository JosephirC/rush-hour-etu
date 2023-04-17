#include "puzzle.hpp"
#include <cstdlib>
#include <fstream>
#include <algorithm>

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

Position Puzzle::taxiExit(){

    Position exit;
    
    int randomSide = rand() % 2;

    if(taxiDirection == HORIZONTAL){
        if(randomSide == 0){ // Exit left
            exit.x = taxiPosX;
            exit.y = 0;
        }
        else{ // Exit right
            exit.x = taxiPosX;
            exit.y = taxiPosY + (WIDTH - taxiPosY - 1); 
        }
    }

    if(taxiDirection == VERTICAL){
        if(randomSide == 0){ // Exit up
            exit.x = 0;
            exit.y = taxiPosY;
        }
        else{ //Exit down 
            exit.x = taxiPosX + (HEIGHT - taxiPosX - 1);
            exit.y = taxiPosY;
        }
    }

    return exit;
}


void Puzzle::setNumberOfCars(int s){
    numberOfCars = s;
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

    // srand(time(0));

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

                        // if (i==0) {

                        //     taxiPosX = x;
                        //     taxiPosY = y;
                        //     //taxiSize = size;
                        //     taxiDirection = direction;

                        //     Position exit = taxiExit();

                        //     exitPosX = exit.x;
                        //     exitPosY = exit.y;


                        //     grid.setExitPosX(exitPosX);
                        //     grid.setExitPosY(exitPosY);

                        //     std::cout << "pos voiture : " << x << ", " << y << std::endl;
                        //     std::cout << "pos sortie : " << exitPosX << ", " << exitPosY << std::endl;
                        // }

                        if (i==0) {
                            grid.setExitPosX(5);
                            grid.setExitPosY(y);

                            std::cout << "pos voiture : " << x << ", " << y << std::endl;
                            std::cout << "pos sortie : " << 5 << ", " << y << std::endl;
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
                        // if (i==0) {

                        //     taxiPosX = x;
                        //     taxiPosY = y;
                        //     //taxiSize = size;
                        //     taxiDirection = direction;

                        //     Position exit = taxiExit();

                        //     exitPosX = exit.x;
                        //     exitPosY = exit.y;


                        //     grid.setExitPosX(exitPosX);
                        //     grid.setExitPosY(exitPosY);

                        //     std::cout << "pos voiture : " << x << ", " << y << std::endl;
                        //     std::cout << "pos sortie : " << exitPosX << ", " << exitPosY << std::endl;
                        // }
                        
                        if (i==0) {
                            grid.setExitPosX(x);
                            grid.setExitPosY(5);

                            std::cout << "pos voiture : " << x << ", " << y << std::endl;
                            std::cout << "pos sortie : " << x << ", " << 5 << std::endl;
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
    std::cout << "nombre de voitures :" << numberOfCars << std::endl;

    makeEmptyGrid();

    randomGrid(numberOfCars);

    grid.displayGridId(); //test ok

    return grid;
}

void Puzzle::puzzleToSVG(Puzzle p){

    ofstream file("./puzzle/puzzle.svg");
    file << p.grid.svgHeader() << p.grid.svgRectangle() << p.grid.svgFooter(); 
}