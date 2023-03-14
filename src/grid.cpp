#include "grid.hpp"
#include "car.hpp"
#include <fstream>
#include <sstream>
#include <exception>

Grid::Grid(int _width, int _length) :
width(6),
length(6)
{
    width = _width;
    length = _length;
}

void Grid::initEmptyGrid(){
    
    for(int i = 0; i < length; i++){
        for(int j = 0; j < width; j++){
            cout << ". ";
        } cout << endl;
    }
    cout << endl;
    
    for(int i = 0; i < length; i++){
        for(int j = 0; j < width; j++){
            grilleIDCar[i][j] = -1; // -1 = case vide
        }
    }
}

void Grid::displayGrid(){
    for(int i = 0; i < length; i++){
        for(int j = 0; j < width; j++){
            cout << grilleIDCar[i][j] << " ";
        } cout << endl;
    }
    cout << endl;
}

void Grid::addCar(const Car& v){
    carArray.push_back(v);
    int posX = v.getPosX();
    int posY = v.getPosY();
    grilleIDCar[posX][posY] = v.getId();
    if (v.getDirection() == 0) {
        for (int i=1; i< v.getSize(); i++) {
            grilleIDCar[posX+i][posY] = v.getId();
        }
    }
    else {
        for (int i=1; i< v.getSize(); i++) {
            grilleIDCar[posX][posY+i] = v.getId();
        }
    }
}

int Grid::getEndX() const{
    return endPosX;
}

int Grid::getEndY() const{
    return endPosY;
}

int Grid::getSizeX() {
    return length;
}

int Grid::getSizeY() {
    return width;
}

vector<Car> Grid::getCarArray() {
    return carArray;
}

void Grid::displayCarArray(){
    for(int i = 0; i < carArray.size(); i++){
        cout << "Car --> Id = " << carArray[i].getId() << " X = " << carArray[i].getPosX() << " Y = " << carArray[i].getPosY() 
        << " Size = " << carArray[i].getSize() << " Direction " << carArray[i].getDirection() << endl; 
    }
}

void Grid::loadData(const string& filename){
    
    //Lire la premiere ligne (stocker les coordonnees pour sortir la voiture)
    ifstream file(filename.c_str());

    if (file.good())
    {
        int sortieX, sortieY;
        string premiereLine;
        //getline(file, premiereLine);
        
        if(file >> sortieX >> sortieY){
            endPosX = sortieX;
            endPosY = sortieY;
        }
        else{
            throw length_error("Impossible de lire la sortie du plateau");
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

string Grid::HeaderSVG() const {
    stringstream ss;
    ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 " 
       << width * TAILLE_CASE << " " << length * TAILLE_CASE 
       << "\" width=\"" << width * TAILLE_CASE << "\" height=\"" 
       << length * TAILLE_CASE << "\" stroke=\"" << STROKE_COLOR 
       << "\" stroke-width=\"" << STROKE_WIDTH << "\" fill=\"none\">" << endl;
    ss << "<rect x=\"0\" y=\"0\" width=\"" << width * TAILLE_CASE 
       << "\" height=\"" << length * TAILLE_CASE << "\" stroke=\"" 
       << STROKE_COLOR << "\" stroke-width=\"" << 15 * STROKE_WIDTH 
       << "\" fill=\"none\" />" << endl;
    return ss.str();
}

string Grid::RectangleSVG() const {
    stringstream ss;
    for (const auto& car : carArray) {
        const int x = car.getPosY() * TAILLE_CASE + MARGE;
        const int y = car.getPosX() * TAILLE_CASE + MARGE;
        const int width = (car.getDirection() == 0) ? TAILLE_CASE - 2 * MARGE : 
                                                       car.getSize() * TAILLE_CASE - 2 * MARGE;
        const int height = (car.getDirection() == 0) ? car.getSize() * TAILLE_CASE - 2 * MARGE : 
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

string Grid::FooterSVG() const {
    return "</svg>";
}

void Grid::addGameSituation() {
    for (const auto& car : carArray) {
        if (car.getDirection() == 0) { // Verticale
                if (grilleIDCar[car.getPosX() - 1][car.getPosY()] == -1) { // Si la voiture a une case vide derrière elle, elle peut avancer
                    // ajouter une situation de jeu avec la voiture qui s'est déplacée sur la case vide
                }
                if (grilleIDCar[car.getPosX() + car.getSize()][car.getPosY()] == -1) { // Si la voiture a une case vide devant elle, elle peut avancer
                    // ajouter une situation de jeu avec la voiture qui s'est déplacée sur la case vide
                }
            } 

        if (car.getDirection() == 1) { // Verticale
            if (grilleIDCar[car.getPosX()][car.getPosY() - 1] == -1) { // Si la voiture a une case vide derrière elle, elle peut avancer
                    // ajouter une situation de jeu avec la voiture qui s'est déplacée sur la case vide
                }
                if (grilleIDCar[car.getPosX()][car.getPosY() + car.getSize()] == -1) { // Si la voiture a une case vide devant elle, elle peut avancer
                    // ajouter une situation de jeu avec la voiture qui s'est déplacée sur la case vide
                }
        }
    }
}