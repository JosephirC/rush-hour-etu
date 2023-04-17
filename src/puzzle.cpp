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

void Puzzle::randCar(int gridCarId[6][6]){ //gridCarId = -1 au debut et on l'update au fur et a mesure

    cout << numberOfCars << " defsgvd" << endl; 

    for(int i = 0; i < numberOfCars; i++){

        int direction = rand()%2;
        vector<int> line;
        bool putCar = false;

        if(direction == HORIZONTAL){ // horizontal
            int x = rand()%6;
            int y;
            int yy = 0;
            int size;
            while(gridCarId[x][yy] ==-1 && yy < WIDTH){ // cette boucle me permet de stocker les y qui sont vides
                line.push_back(yy);
                yy++;
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

                            grid.setGridCarId(x, y, i);
                            grid.setGridCarId(x, y + size - 1, i);
                            grid.setGridCarId(x, y + size, i);

                            line.erase(line.begin() + n);
                            putCar = true;

                        }
                        // else{
                        //     break;
                        // }
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
                xx++;
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

                            grid.setGridCarId(x, y, i);
                            grid.setGridCarId(x + size - 1, y, i);
                            grid.setGridCarId(x + size, y, i);

                            line.erase(line.begin() + n);
                            line.erase(line.begin() + n+size-1);
                            line.erase(line.begin() + n+size);
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

/*

    grid.setGridCarId(x, y, i);
    grid.setGridCarId(x, y + size - 1, i);
    grid.setGridCarId(x, y + size, i);

    grid.setGridCarId(x, y, i);
    grid.setGridCarId(x + size - 1, y, i);
    grid.setGridCarId(x + size, y, i);

*/

void Puzzle::randCar2(int gridCarId[6][6]){
    
    cout << numberOfCars << " defsgvd" << endl; 

    int count = 0;

    for(int i = 0; i < numberOfCars; i++){
        int direction = rand()%2;
        vector<int> line;
        bool putCar = false;
        
        if(direction == HORIZONTAL){
            int x = rand()%6;
            int y;
            int size = rand() % 2 + 2;
            for (int yy = 0; yy < WIDTH; yy++) { // Check for available spaces in the line
                if(gridCarId[x][yy] == -1 && gridCarId[x][yy + size - 2] == -1 && gridCarId[x][yy + size-1] == -1
                && gridCarId[x][yy] < WIDTH && gridCarId[x][yy + size - 2] < WIDTH && gridCarId[x][yy + size-1] < WIDTH){
                    line.push_back(yy);

                    cout << "direction : " << direction << endl;
                    cout << "x : " << x << ", y : " << yy << ", k : " << size  << endl;
                    cout << "Grid value at " << x << ", " << yy  << " : " << gridCarId[x][yy+size] << endl << endl ;

                }
            }

            if(!line.empty()){ // Check if there are any valid spaces in the line
                int n = rand() % line.size();
                y = line[n];
                

                //cout << "x : " << x << " y : " << y << endl;

                car.setPosX(x);
                car.setPosY(y);
                car.setDirection(direction);
                car.setSize(size);
                car.setId(i);
                grid.addCar(car);
                count++;

                // for (int j = 0; j < size; j++) { // Mark the car's cells in the gridCarId array
                //     gridCarId[x][y+j] = i;
                // }

                grid.setGridCarId(x, y, i);
                grid.setGridCarId(x, y + size - 2, i);
                grid.setGridCarId(x, y + size - 1, i);

                // line.erase(line.begin() + n);
                // line.erase(line.begin() + n+size-2);
                // line.erase(line.begin() + n+size-1);

                putCar = true;
            }
        }
        else if(direction == VERTICAL){
            int x;
            int y = rand()%6;
            int size = rand() % 2 + 2;
            for (int xx = 0; xx < HEIGHT; xx++) { // Check for available spaces in the column
                if(gridCarId[xx][y] == -1 && gridCarId[xx + size -2 ][y] == -1 && gridCarId[xx + size-1][y] == -1
                && gridCarId[xx][y] < HEIGHT && gridCarId[xx + size -2 ][y] < HEIGHT && gridCarId[xx + size-1][y] < HEIGHT){
                    line.push_back(xx);

                    cout << "direction : " << direction << endl;
                    cout << "x : " << xx << ", y : " << y << ", k : " << size  << endl;
                    cout << "Grid value at " << xx << ", " << y  << " : " << gridCarId[xx + size][y] << endl << endl ;

                }
            }

            if(!line.empty()){ // Check if there are any valid spaces in the column
                int n = rand() % line.size();
                x = line[n];
                size = rand() % 2 + 2;

                //cout << "x : " << x << " y : " << y << endl;

                car.setPosX(x);
                car.setPosY(y);
                car.setDirection(direction);
                car.setSize(size);
                car.setId(i);
                grid.addCar(car);

                count++;

                // for (int j = 0; j < size; j++) { // Mark the car's cells in the gridCarId array
                //     gridCarId[x+j][y] = i;
                // }

                grid.setGridCarId(x, y, i);
                grid.setGridCarId(x + size - 2, y, i);
                grid.setGridCarId(x + size - 1, y, i);

                // line.erase(line.begin() + n);
                // line.erase(line.begin() + n+size-2);
                // line.erase(line.begin() + n+size-1);

                putCar = true;
            }
        }
        if(!putCar){ // If the car was not put, decrement i to try again
            i--;
        }
    }
    // Check if all the cars have been drawn, and try again if not
    cout << "dcount" << count << endl;
    // if(count< numberOfCars){
    //     cout << " no " << endl;
    //     randCar2(gridCarId);
    // }
}

// void Puzzle::randCar2(int gridCarId[6][6]){
    
//     cout << numberOfCars << " defsgvd" << endl; 
//     int count = 0;

//     for(int i = 0; i < numberOfCars; i++){
//         int direction = rand()%2;
//         vector<int> line;
//         bool putCar = false;
        
//         if(direction == HORIZONTAL){
//             int x = rand()%6;
//             int y;
//             int size = rand() % 2 + 2;
//             for (int yy = 0; yy <= WIDTH; yy++) { // Check for available spaces in the line
//                 bool validSpace = false;
//                 for (int k = 0; k < size; k++) {

//                     cout << "x : " << x << ", y : " << yy+k << ", k : " << k  << endl;
//                     cout << "Grid value at " << x << ", " << yy+k  << " : " << gridCarId[x][yy+k] << endl << endl ;

//                     if (gridCarId[x][yy + k] == -1) {
//                         validSpace = true;
//                         break;
//                     }
//                 }
//                 if (!validSpace) {
//                     line.push_back(yy);
//                 }
//             }

//             if(!line.empty()){ // Check if there are any valid spaces in the line
//                 int n = rand() % line.size();
//                 y = line[n];
                
//                 // Check if car is inside the grid
//                 if(x >= 0 && x < HEIGHT && y >= 0 && y + size - 1 < WIDTH) {
//                     car.setPosX(x);
//                     car.setPosY(y);
//                     car.setDirection(direction);
//                     car.setSize(size);
//                     car.setId(i);
//                     grid.addCar(car);
//                     count++;

//                     for (int k = 0; k < size; k++) {
//                         grid.setGridCarId(x, y + k, i);
//                         line.erase(find(line.begin(), line.end(), y + k));
//                     }

//                     putCar = true;
//                 }
//             }
//         }
//         else if(direction == VERTICAL){
//             int x;
//             int y = rand()%6;
//             int size = rand() % 2 + 2;
//             for (int xx = 0; xx <= HEIGHT; xx++) { // Check for available spaces in the column
//                 bool validSpace = false;
//                 for (int k = 0; k < size; k++) {

//                     cout << "x : " << xx+k << ", y : " << y << ", k : " << k  << endl;
//                     cout << "Grid value at " << xx+k << ", " << y  << " : " << gridCarId[xx + k][y] << endl << endl ;

//                     if (gridCarId[xx + k][y] != -1) {
//                         validSpace = true;
//                         break;
//                     }
//                 }
//                 if (!validSpace) {
//                     line.push_back(xx);
//                 }
//             }

//             if(!line.empty()){ // Check if there are any valid spaces in the column
//                 int n = rand() % line.size();
//                 x = line[n];
//                 size = rand() % 2 + 2;

//                 // Check if car is inside the grid
//                 if(x >= 0 && x + size - 1 < HEIGHT && y >= 0 && y < WIDTH) {
//                     car.setPosX(x);
//                     car.setPosY(y);
//                     car.setDirection(direction);
//                     car.setSize(size);
//                     car.setId(i);
//                     grid.addCar(car);
//                     count++;

//                     for (int k = 0; k < size; k++) {
//                         grid.setGridCarId(x + k, y, i);
//                         line.erase(find(line.begin(), line.end(), x + k));
//                     }

//                     putCar = true;
//                 }
//             }
//         }
//         if(!putCar){ // If the car was not put, decrement i to try again
//             i--;
//         }
//     }
//     cout << "dcount" << count << endl;
// }


Grid Puzzle::generateRandomPuzzle(){
    
    makeEmptyGrid();

    grid.displayGridId(); //test ok

    int gridCarId[6][6];
    grid.getGridCarId(gridCarId);
    randCar2(gridCarId);

    grid.displayGridId();


        // on rajoute le cas initial
        ofstream file("./puzzle/.svg");
        file << grid.svgHeader() << grid.svgRectangle() << grid.svgFooter(); 



    
    return grid;

}