#include "puzzle.hpp"
#include <cstdlib>
#include <fstream>

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

int Puzzle::randCar(int &gridCarId[6][6]){ //gridCarId = -1 au debut et on l'update au fur et a mesure

    for(int i = 0; i < numberOfCars; i++){

        int direction = rand()%2;
        int vector<int> line;
        bool putCar = false;

        if(direction == HORIZONTAL){ // horizontal
            int x = rand()%6;
            int y;
            int yy = 0;
            int size;
            while(gridCarId[x][yy] ==-1 && yy < WIDTH){ // cette boucle me permet de stocker les y qui sont vides
                line.push_back(yy);
                yy++
            }

            //if(line.size() < 3){ // je n'ajoute une voiture que si j'ai au moins 3 cases vides dans la ligne que je teste
                while(!putCar){
                    if(!line.empty()){
                        int n = rand() % line.size(); // je tire un y aleatoire de mon vector
                        y = line[n];
                        size = rand() % 2 + 2;

                        if(gridCarId[x][y] == -1 && gridCarId[x][y + size - 1] == -1 && gridCarId[x][y + size] == -1){
                            car.setPosX(x);
                            car.setPosY(y);
                            car.setDirection(direction);
                            car.setSize(size);
                            car.setId(i);
                            grid.addCar(car);

                            gridCarId[x][y] = i;
                            gridCarId[x][y + size - 1] = i;
                            gridCarId[x][y + size] = i;

                            line.erase(line.begin() + n);
                            putCar = true;

                        }
                        else{
                            break;
                        }
                    }
                }
            //}
        }
        else if(direction == VERTICAL){ // horizontal
            int x;
            int y = rand()%6;
            int xx = 0;
            int size;
            while(gridCarId[xx][y] ==-1 && xx < HEIGHT){ // cette boucle me permet de stocker les y qui sont vides
                line.push_back(xx);
                xx++
            }

            //if(line.size() < 3){ // je n'ajoute une voiture que si j'ai au moins 3 cases vides dans la ligne que je teste
                while(!putCar){
                    if(!line.empty()){
                        int n = rand() % line.size(); // je tire un y aleatoire de mon vector
                        x = line[n];
                        size = rand() % 2 + 2;

                        if(gridCarId[x][y] == -1 && gridCarId[x + size - 1][y] == -1 && gridCarId[x + size][y] == -1){
                            car.setPosX(x);
                            car.setPosY(y);
                            car.setDirection(direction);
                            car.setSize(size);
                            car.setId(i);
                            grid.addCar(car);

                            gridCarId[x][y] = i;
                            gridCarId[x + size - 1][y] = i;
                            gridCarId[x + size][y] = i;

                            line.erase(line.begin() + n);
                            putCar = true;

                        }
                        else{
                            break;
                        }
                    }
                }
            //}
        }
    }
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


Grid Puzzle::generateRandomPuzzle(){
    
    makeEmptyGrid();

    grid.displayGridId(); //test ok


    //randomCar(grid.get)

    // grid.displayGridId();

    //     // on rajoute le cas initial
    //     ofstream file("./puzzle/.svg");
    //     file << grid.svgHeader() << grid.svgRectangle() << grid.svgFooter(); 



    
    return grid;

}