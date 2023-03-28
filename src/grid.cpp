#include "grid.hpp"
#include "car.hpp"
#include <fstream>
#include <sstream>
#include <exception>

Grid::Grid(int _width, int _height) :
width(6),
height(6)
{
    width = _width;
    height = _height;
}

void Grid::initEmptyGrid(){

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            gridCarId[i][j] = -1; // -1 = case vide
        }
    }

    //Display empty grid
    cout << endl << "initEmptyGrid" << endl;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            cout << " " << gridCarId[i][j] << " ";
        } cout << endl;
    }
    cout << endl;

}

void Grid::addCar(const Car& c){
    carArray.push_back(c);
    int posX = c.getPosX();
    int posY = c.getPosY();
    gridCarId[posX][posY] = c.getId();
    if (c.getDirection() == 0) {
        for (int i = 1; i< c.getCarSize(); i++) {
            gridCarId[posX+i][posY] = c.getId();
        }
    }
    else {
        for (int i = 1; i< c.getCarSize(); i++) {
            gridCarId[posX][posY+i] = c.getId();
        }
    }
}

void Grid::displayGridId(){
    cout << endl << "displayGridId" << endl;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            cout << "  " << gridCarId[i][j] << "  ";
            //cout << gridCarId;
        } cout << endl;
    }
    cout << endl;
}

int Grid::getExitX() const{
    return exitPosX;
}

int Grid::getExitY() const{
    return exitPosY;
}

int Grid::getSizeX() const {
    return width;
}

int Grid::getSizeY() const {
    return height;
}

vector<Car> Grid::getCarArray() {
    return carArray;
}

void Grid::displayCarArray(){
    cout << endl << "displayCarArray" << endl;
    for(int i = 0; i < carArray.size(); i++){
        cout << "Car --> Id = " << carArray[i].getId() << "  X = " << carArray[i].getPosX() << "  Y = " << carArray[i].getPosY() 
        << "  Size = " << carArray[i].getCarSize() << "  Direction " << carArray[i].getDirection() << endl; 
    }
}

void Grid::loadData(const string& filename){
    
    //Lire la premiere ligne (stocker les coordonnees pour sortir la voiture)
    ifstream file(filename.c_str());

    if (file.good())
    {
        int finishX, finishY;
        string firstLine;
        //getline(file, premiereLine);
        
        if(file >> finishX >> finishY){
            exitPosX = finishX;
            exitPosY = finishY;
        }
        else{
            throw length_error("Impossible to read the grid exit");
        }
        
        int pX, pY; //position X et Y
        int t; //taille du vehicule
        int dir; //direction du vehicule
        int id = 0;

        while(file >> pX >> pY >> t >> dir){
            
            Car c(pX, pY, t, dir, id);
            addCar(c);
            id++;
        }
    }
    else
        throw invalid_argument("Failed to open file...");
    
}

// string Grid::HeaderSVG() const{
//     stringstream ss;
//     ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 \" width=\"" 
//         << width * TAILLE_CASE << "\" height=\"" << length * TAILLE_CASE << "\" stroke=\"black\" stroke-width=\"1\" fill=\"none\" >" << endl
//         << "<rect x=\"0""\" y=\"0""\" width=\"600""\" height=\"600""\" stroke=\"black""\" stroke-width=\"15""\" fill=\"none""\" />" << endl;
//     return ss.str();
// }

// string Grid::RectangleSVG() const{
//     stringstream ss;
//     for (int i = 0; i < carArray.size(); i++) {
//         if(carArray[i].getDirection() == 0){
//              ss << "<rect x=\"" << (carArray[i].getPosY() * TAILLE_CASE) + MARGE << "\" y=\"" << (carArray[i].getPosX() * TAILLE_CASE) + MARGE
//             << "\" width=\"" << TAILLE_CASE - (MARGE * 2) << "\" height=\""
//             << (carArray[i].getTaille() * TAILLE_CASE) - (MARGE * 2) << "\" fill=\"red\" />" << endl;
//         }
//         else{
//             ss << "<rect x=\"" << (carArray[i].getPosY() * TAILLE_CASE) + MARGE << "\" y=\"" << (carArray[i].getPosX() * TAILLE_CASE) + MARGE
//             << "\" width=\"" << (carArray[i].getTaille() * TAILLE_CASE) - (MARGE * 2) << "\" height=\""
//             << TAILLE_CASE - (MARGE * 2) << "\" fill=\"red\" />" << endl;
//         }
//     }
//     return ss.str();
// }

// string Grid::FooterSVG() const{
//     stringstream ss;
//     ss << "</svg>";
//     return ss.str();
// }

const int STROKE_WIDTH = 1;
const string STROKE_COLOR = "black";
const string FILL_COLOR = "red";

string Grid::svgHeader() const {
    stringstream ss;
    ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 " 
       << width * TAILLE_CASE << " " << height * TAILLE_CASE 
       << "\" width=\"" << width * TAILLE_CASE << "\" height=\"" 
       << height * TAILLE_CASE << "\" stroke=\"" << STROKE_COLOR 
       << "\" stroke-width=\"" << STROKE_WIDTH << "\" fill=\"none\">" << endl;
    ss << "<rect x=\"0\" y=\"0\" width=\"" << width * TAILLE_CASE 
       << "\" height=\"" << height * TAILLE_CASE << "\" stroke=\"" 
       << STROKE_COLOR << "\" stroke-width=\"" << 15 * STROKE_WIDTH 
       << "\" fill=\"none\" />" << endl;
    return ss.str();
}

string Grid::svgRectangle() const {
    stringstream ss;
    for (const auto& car : carArray) {
        const int x = car.getPosY() * TAILLE_CASE + MARGE;
        const int y = car.getPosX() * TAILLE_CASE + MARGE;
        const int width = (car.getDirection() == 0) ? TAILLE_CASE - 2 * MARGE : 
                                                       car.getCarSize() * TAILLE_CASE - 2 * MARGE;
        const int height = (car.getDirection() == 0) ? car.getCarSize() * TAILLE_CASE - 2 * MARGE : 
                                                        TAILLE_CASE - 2 * MARGE;

        if (car.getId() == 0) {
            ss << "<rect x=\"" << x << "\" y=\"" << y 
           << "\" width=\"" << width << "\" height=\"" << height 
           << "\" fill=\"" << "green" << "\" />" << endl;
        }
        else {
            ss << "<rect x=\"" << x << "\" y=\"" << y 
           << "\" width=\"" << width << "\" height=\"" << height 
           << "\" fill=\"" << FILL_COLOR << "\" />" << endl;
        }
    }
    return ss.str();
}

string Grid::svgFooter() const {
    return "</svg>";
}

void Grid::addGameSituation() {
    for (const auto& car : carArray) {
        if (car.getDirection() == 0) { // Verticale
                if (gridCarId[car.getPosX() - 1][car.getPosY()] == -1) { // Si la voiture a une case vide derrière elle, elle peut avancer
                    // ajouter une situation de jeu avec la voiture qui s'est déplacée sur la case vide
                }
                if (gridCarId[car.getPosX() + car.getCarSize()][car.getPosY()] == -1) { // Si la voiture a une case vide devant elle, elle peut avancer
                    // ajouter une situation de jeu avec la voiture qui s'est déplacée sur la case vide
                }
            } 

        if (car.getDirection() == 1) { // Verticale
            if (gridCarId[car.getPosX()][car.getPosY() - 1] == -1) { // Si la voiture a une case vide derrière elle, elle peut avancer
                    // ajouter une situation de jeu avec la voiture qui s'est déplacée sur la case vide
                }
                if (gridCarId[car.getPosX()][car.getPosY() + car.getCarSize()] == -1) { // Si la voiture a une case vide devant elle, elle peut avancer
                    // ajouter une situation de jeu avec la voiture qui s'est déplacée sur la case vide
                }
        }
    }
}

vector<int> Grid::getNeighborCars(int carId){
    vector<int> neighbors;
    Car car = carArray[carId];
    int x = car.getPosX();
    int y = car.getPosY();
    int size = car.getCarSize();
    int direction = car.getDirection();

    //Direction horizontale
    if(direction == 0){
        if(x > 0 && gridCarId[x][y-1] != -1)
            neighbors.push_back(gridCarId[x][y-1]);
        
        if(x + size < width && gridCarId[x][y+size] != -1)
            neighbors.push_back(gridCarId[x][y+size]);
    }

    //Direction verticale
    if(direction == 1){
        if(y > 0 && gridCarId[x-1][y] != -1)
            neighbors.push_back(gridCarId[x-1][y]);

        if(y + size  < height && gridCarId[x+size][y] != -1)
            neighbors.push_back(gridCarId[x+size][y]);
    }

    return neighbors;
}