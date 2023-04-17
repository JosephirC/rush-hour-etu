#include "puzzle.hpp"
#include <cstdlib>
#include <algorithm>
#include <ctime>

Puzzle::Puzzle(){

    srand(time(0));

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

int Puzzle::randomCar(int gridCarId[6][6]) {

    if (freePositions.size() < 2)
        return 1;

    int r = rand() % (freePositions.size()-1);

    string num = freePositions[r];
    int x = std::stoi(std::string(1, num[0]));
    int y = std::stoi(std::string(1, num[1]));


    int direction;
    int size;
    std::string s_x;
    std::string s_y;
    std::string s;


    if (gridCarId[x+1][y] != -1 ) {
            direction = 1;
            if (gridCarId[x][y+1] != -1 ) {
                std::cout << x << ", " << y << " : probleme" << std::endl;
                randomCar(gridCarId); // on ne peut pas placer de voiture ici, on rappelle la fonction pour changer de position
                return 1;
            }
            else if (gridCarId[x][y+1] == -1 && gridCarId[x][y+2] == -1 ) {
                direction = 1;
                std::cout << "point " << x << ", " << y << " : je supprime" << std::endl;
                size = 3;
                s_x = std::to_string(x);
                s_y = std::to_string(y);
                s = s_x+s_y;
                std::cout << s << std::endl;
                freePositions.erase(std::remove(freePositions.begin(), freePositions.end(), s), freePositions.end()); // delete l'element égal aux coordonnées x,y 
                
                s_x = std::to_string(x);
                s_y = std::to_string(y+1);
                s = s_x+s_y;
                std::cout << s << std::endl;

                freePositions.erase(std::remove(freePositions.begin(), freePositions.end(), s), freePositions.end());
                
                s_x = std::to_string(x);
                s_y = std::to_string(y+2);
                s = s_x+s_y;
                std::cout << s << std::endl;

                freePositions.erase(std::remove(freePositions.begin(), freePositions.end(), s), freePositions.end());
            }
            else if (gridCarId[x][y+1] == -1 && gridCarId[x][y+2] != -1 ) {
                direction = 1;
                std::cout << "point " << x << ", " << y << " : je supprime" << std::endl;

                size = 2;
                s_x = std::to_string(x);
                s_y = std::to_string(y);
                s = s_x+s_y;
                std::cout << s << std::endl;

                freePositions.erase(std::remove(freePositions.begin(), freePositions.end(), s), freePositions.end()); // delete l'element égal aux coordonnées x,y 
                
                s_x = std::to_string(x);
                s_y = std::to_string(y+1);
                s = s_x+s_y;
                std::cout << s << std::endl;

                freePositions.erase(std::remove(freePositions.begin(), freePositions.end(), s), freePositions.end());
            }
    }
    else if (gridCarId[x+1][y] == -1 && gridCarId[x+2][y] == -1 ) {
            direction = 0;

            std::cout << "point " << x << ", " << y << " : je supprime" << std::endl;

            size = 3;
            s_x = std::to_string(x);
            s_y = std::to_string(y);
            s = s_x+s_y;
                std::cout << s << std::endl;

            freePositions.erase(std::remove(freePositions.begin(), freePositions.end(), s), freePositions.end()); // delete l'element égal aux coordonnées x,y 
            
            s_x = std::to_string(x+1);
            s_y = std::to_string(y);
            s = s_x+s_y;
                std::cout << s << std::endl;

            freePositions.erase(std::remove(freePositions.begin(), freePositions.end(), s), freePositions.end());
            
            s_x = std::to_string(x+2);
            s_y = std::to_string(y);
            s = s_x+s_y;
                std::cout << s << std::endl;

            freePositions.erase(std::remove(freePositions.begin(), freePositions.end(), s), freePositions.end());
        }
    else if (gridCarId[x+1][y] == -1 && gridCarId[x+2][y] != -1 ) {
            direction = 0;

            std::cout << "point " << x << ", " << y << " : je supprime" << std::endl;

            size = 2;
            s_x = std::to_string(x);
            s_y = std::to_string(y);
            s = s_x+s_y;
                std::cout << s << std::endl;


            freePositions.erase(std::remove(freePositions.begin(), freePositions.end(), s), freePositions.end()); // delete l'element égal aux coordonnées x,y 
            s_x = std::to_string(x+1);
            s_y = std::to_string(y);
            s = s_x+s_y;
                std::cout << s << std::endl;


            freePositions.erase(std::remove(freePositions.begin(), freePositions.end(), s), freePositions.end());
    }
        

    car.setPosX(x);
    car.setPosY(y);
    car.setDirection(direction);
    car.setSize(size);

    return 1;  // succès
}

//RULE : always min = 6, max = 13
Grid Puzzle::generateRandomGrid(int carMin, int carMax){
    
    numberOfCars = randomNumberOfCars(carMin, carMax);
    std::cout << "nombre de voitures :" << numberOfCars << std::endl;

    makeEmptyGrid();

    grid.displayGridId(); //test ok

    int gridCarId[6][6];

    car.setId(0);
    car.setPosX(2);
    car.setPosY(0);
    car.setDirection(1);
    car.setSize(2);   
    freePositions.erase(std::remove(freePositions.begin(), freePositions.end(), "20"), freePositions.end()); // delete l'element égal aux coordonnées x,y 
    freePositions.erase(std::remove(freePositions.begin(), freePositions.end(), "21"), freePositions.end()); // delete l'element égal aux coordonnées x,y 


    grid.setExitPosX(2);
    grid.setExitPosY(5);
    grid.addCar(car);


    for(int i = 1; i < numberOfCars; i++){

        grid.getGridCarId(gridCarId);
        int test = randomCar(gridCarId);
        while (test == 0) {
            int test = randomCar(gridCarId);
        }
        car.setId(i);

        grid.addCar(car);

        // for(int h = 0; h < 6; h++){
        //     for(int j = 0; j < 6; j++){
        //         cout << "  " << gridCarId[h][j] << "  ";
        //     } cout << endl;
        // }
        // cout << endl;

        // while (overlap) {
        //     if (car.getDirection() == 1) {
        //         if (gridCarId[car.getPosX()][car.getPosY()] == -1 && gridCarId[car.getPosX()][car.getPosY()+car.getSize()-1] == -1 && gridCarId[car.getPosX()][car.getPosY()+car.getSize()] == -1) {
        //             grid.addCar(car);
        //             overlap = false;

        //         }
        //     }
        //     else if (car.getDirection() == 0) {
        //         if (gridCarId[car.getPosX()][car.getPosY()] == -1 && gridCarId[car.getPosX()+car.getSize()-1][car.getPosY()] == -1 && gridCarId[car.getPosX()+car.getSize()][car.getPosY()] == -1) // vertical
        //         {
        //             grid.addCar(car);
        //             overlap = false;
        //         }
        //     }
        //     else {
        //         car.setPosX(randomCarsPos());
        //         car.setPosY(randomCarsPos());
        //         car.setSize(randomCarsSize());
        //         car.setDirection(randomCarsDirection());
        //         car.setId(i);
        //     }
        // }

    }

    grid.displayGridId(); //test ok

    
    return grid;
}