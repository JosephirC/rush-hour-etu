#include "grid.hpp"
#include "car.hpp"
#include <fstream>
#include <sstream>
#include <exception>
#include <cstring>

Grid::~Grid() {
    if (parent != nullptr)
        delete this;
}

Grid::Grid(){
    width = 0;
    height = 0;
    exitPosX = -1;
    exitPosY = -1;
    parent = nullptr;
    gridString = ""; 
}

Grid::Grid(int _width, int _height) :
width(_width),
height(_height)
{
    exitPosX = -1;
    exitPosY = -1;
    parent = nullptr;
    gridString = "";
}

Grid::Grid(const Grid& grid) { //constructeur par copie
    width = grid.width;
    height = grid.height;
    exitPosX = grid.exitPosX;
    exitPosY = grid.exitPosY;
    gridString = grid.gridString;
    carArray = grid.carArray;

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            gridCarId[i][j] = grid.gridCarId[i][j];
        }
    }

    neighbours = grid.neighbours;
    parent = grid.parent;
}

// Grid::Grid(const Grid* other) { // constructeur par copie
//     width = other->width;
//     height = other->height;
//     exitPosX = other->exitPosX;
//     exitPosY = other->exitPosY;
//     carArray = other->carArray;
//     memcpy(gridCarId, other->gridCarId, sizeof(gridCarId));
//     parent = other->parent;
//     neighbours = other->neighbours;
// }

Grid Grid::operator=(const Grid& grid) {
    this->width = grid.width;
    this->height = grid.height;
    this->exitPosX = grid.exitPosX;
    this->exitPosY = grid.exitPosY;
    for (int i=0; i<grid.carArray.size(); i++) {
        this->carArray.push_back(grid.carArray[i]);
    }
    for(int i = 0; i < this->width; i++){
        for(int j = 0; j < this->height; j++){
            this->gridCarId[i][j] = grid.gridCarId[i][j];
        }
    }
    for (int i=0; i<grid.neighbours.size(); i++) {
        this->neighbours.push_back(grid.neighbours[i]);
    }
    this->parent = grid.parent;

    return *this;
}

// Grid Grid::operator=(const Grid& other) {
//     if (this != &other) {
//         width = other.width;
//         height = other.height;
//         exitPosX = other.exitPosX;
//         exitPosY = other.exitPosY;
//         carArray = other.carArray;
//         parent = other.parent;
//         for (auto neighbor : other.neighbours) {
//             neighbours.push_back(new Grid(*neighbor));
//         }
//     }
//     return *this;
// }

// fonction pour debug (visualiser dans la console)
void Grid::initEmptyGrid(){

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            gridCarId[i][j] = -1; // -1 = case vide
        }
    }
}

string Grid::gridToString() {

    string res;

    res.append(std::to_string(exitPosX));
    res.append(std::to_string(exitPosY));
    for (int i=0; i<carArray.size(); i++) {
        res.append(std::to_string(carArray[i].getPosX()));
        res.append(std::to_string(carArray[i].getPosY()));
        res.append(std::to_string(carArray[i].getCarSize()));
        res.append(std::to_string(carArray[i].getDirection()));
        res.append(std::to_string(carArray[i].getId()));
    }

    return res;
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

void Grid::updateGridCarId(const vector<Car>& carArray) {
    initEmptyGrid();

    for (int i=0; i<carArray.size(); i++) {

        int posX = carArray[i].getPosX();
        int posY = carArray[i].getPosY();

        gridCarId[posX][posY] = carArray[i].getId();
        if (carArray[i].getDirection() == 0) {
            for (int j = 1; j< carArray[i].getCarSize(); j++) {
                gridCarId[posX+j][posY] = carArray[i].getId();
            }
        }
        else {
            for (int j = 1; j< carArray[i].getCarSize(); j++) {
                gridCarId[posX][posY+j] = carArray[i].getId();
            }
        }
    }
}

void Grid::displayGridId(){
    cout << endl << "displayGridId" << endl;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            cout << "  " << gridCarId[i][j] << "  ";
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

Grid* Grid::getParent() const {
    return parent;
}

vector<Car> Grid::getCarArray() const {
    return carArray;
}

string Grid::getGridString() {
    return gridString;
}

void Grid::getGridCarId(int (&gridId)[6][6]) {
    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            gridId[i][j] = gridCarId[i][j];
        }
    }
}

// int** Grid::getGridCarId() {
//     int** ptr = new int*[6];
//     for (int i = 0; i < 6; i++) {
//         ptr[i] = new int[6];
//         for (int j = 0; j < 6; j++) {
//             ptr[i][j] = gridCarId[i][j];
//         }
//     }
//     return ptr;
// }

void Grid::setWidth(int w){
    width = w;
}

void Grid::setHeight(int h){
    height = h;
}

void Grid::setExitPosX(int eX){
    exitPosX = eX;
}

void Grid::setExitPosY(int eY){
    exitPosY = eY;
}

void Grid::setCarArray(vector<Car> car){
    carArray = car;
}

// void Grid::setGridCarId(int gridId[6][6]){
//     for(int i = 0; i < 6; i++){
//         for(int j = 0; j < 6; j++){
//             gridCarId[i][j] = gridId[i][j];
//         }
//     }
// }

void Grid::setParent(Grid* p){
    parent = p;
}

void Grid::setGridString(string s){
    gridString = s;
}

void Grid::displayCarArray() const {
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
        
        if(file >> finishX >> finishY){
            exitPosX = finishX;
            exitPosY = finishY;

            gridString.append(std::to_string(finishX));
            gridString.append(std::to_string(finishY));
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

            gridString.append(std::to_string(pX));
            gridString.append(std::to_string(pY));
            gridString.append(std::to_string(t));
            gridString.append(std::to_string(dir));
            gridString.append(std::to_string(id));

            id++;
        }
    }
    else
        throw invalid_argument("Failed to open file...");
    
}

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

bool Grid::operator==(const Grid& other) const {
    
    if(this->width != other.width && this->height != other.height)
        return false;

    if(this->exitPosX != other.exitPosX && this->exitPosY != other.exitPosY)
        return false;

    for(int i = 0; i < this->carArray.size(); i++){
        if(this->carArray[i].getPosX() != other.carArray[i].getPosX() && this->carArray[i].getPosY() != other.carArray[i].getPosY() 
            && this->carArray[i].getCarSize() != other.carArray[i].getCarSize() && this->carArray[i].getDirection() != other.carArray[i].getDirection() 
            && this->carArray[i].getId() != other.carArray[i].getId()){
                return false;
        }   
    }

    for(int i = 0; i < this->width; i++){
        for(int j = 0; j < this->height; j++){
            if(this->gridCarId[i][j] != other.gridCarId[i][j])
                return false;
        }
    }

    if(this->parent != other.parent){
        return false;
    }

    return true;
}

void Grid::changeCarPosition(int id, int newPosX, int newPosY) {
    carArray[id].setPosX(newPosX);
    carArray[id].setPosY(newPosY);
    gridString = gridToString();
}


bool Grid::isInNeighbours(Grid* grid) const {
    for (int i=0; i<neighbours.size(); i++) {

        if (grid->gridString == gridString) {
            return true;
        }
    }
    return false;
}


vector<Grid*> Grid::getGridNeighbours() {

    for (int i=0; i<carArray.size(); i++) {    
        
        int n = 1; // pour tester sur toute la ligne

        if (carArray[i].getDirection() == 1) { // Horizontal
            while (gridCarId[carArray[i].getPosX()][carArray[i].getPosY() - n] == -1 && (carArray[i].getPosY() - n) >= 0) { // Si la voiture a une case vide à sa gauche, elle peut aller à gauche
                Grid *temp = new Grid(*this);
                temp->changeCarPosition(i, carArray[i].getPosX(), (carArray[i].getPosY() - n));
                temp->updateGridCarId(temp->carArray);
    
                if (!isInNeighbours(temp)) {
                    temp->parent = this;
                    neighbours.push_back(temp);
                }

                n++;
            }

            n = 1;
            while (gridCarId[carArray[i].getPosX()][carArray[i].getPosY() + carArray[i].getCarSize()-1 + n] == -1 && (carArray[i].getPosY() + carArray[i].getCarSize()-1 + n) < width) { // Si la voiture a une case vide à sa droite, elle peut aller à droite
                Grid *temp = new Grid(*this);
                temp->changeCarPosition(i, carArray[i].getPosX(), (carArray[i].getPosY() + n));
                temp->updateGridCarId(temp->carArray);

                if (!isInNeighbours(temp)) {
                    temp->parent = this;
                    neighbours.push_back(temp);
                }

                n++;
            }
        } 

        else if (carArray[i].getDirection() == 0) { // Vertical
            while (gridCarId[carArray[i].getPosX() - n][carArray[i].getPosY()] == -1 && (carArray[i].getPosX() - n) >= 0) { // Si la voiture a une case vide au dessus d'elle, elle peut avancer vers le haut
                Grid *temp = new Grid(*this);
                temp->changeCarPosition(i, (carArray[i].getPosX() - n), carArray[i].getPosY());
                temp->updateGridCarId(temp->carArray);

                if (!isInNeighbours(temp)) {
                    temp->parent = this;
                    neighbours.push_back(temp);
                }

                n++;
            }

            n = 1;
            while (gridCarId[carArray[i].getPosX() + carArray[i].getCarSize()-1 + n][carArray[i].getPosY()] == -1 && (carArray[i].getPosX() + carArray[i].getCarSize()-1 + n) < height) { // Si la voiture a une case vide devant elle, elle peut reculer
                Grid *temp = new Grid(*this);
                temp->changeCarPosition(i, (carArray[i].getPosX() + n), carArray[i].getPosY());
                temp->updateGridCarId(temp->carArray);

                if (!isInNeighbours(temp)) {
                    temp->parent = this;
                    neighbours.push_back(temp);
                }

                n++;
            }
        } 
    }
    
    return neighbours;
}


