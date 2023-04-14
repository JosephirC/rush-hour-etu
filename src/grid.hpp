#ifndef _PLATEAU_HPP
#define _PLATEAU_HPP

#include "car.hpp"
#include <iostream>
#include <vector>

using namespace std;


class Grid {
    private:
        const int MARGE = 20;
        const int TAILLE_CASE = 100;
        int width;
        int height;
        int exitPosX, exitPosY;
        vector<Car> carArray;
        int gridCarId[6][6]; // grille avec pour chaque case l'id de la voiture qui l'occupe
        Grid* parent;
        vector<Grid*> neighbours;

    public : 

        Grid();

        Grid(const Grid& grid); // constructeur par copie

        Grid(int sX, int sY);
        
        void initEmptyGrid();

        string gridToString();

        void addCar(const Car& v);

        void updateGridCarId(const vector<Car>& carArray);

        void displayGridId();

        int getExitX() const;

        int getExitY() const;

        int getSizeX() const;

        int getSizeY() const;
        
        Grid* getParent() const;

        void changeCarPosition(Grid *temp, int id, int newPosX, int newPosY);

        vector<Car> getCarArray() const;

        //void setGridCarId()

        void displayCarArray() const;

        //Utiliser ofstream ou string stream ??? Difference ?
        //reponse : utiliser un string stream pour pouvoir forger les differents svg
        void loadData(const string& filename);
        
        string svgHeader() const;

        string svgRectangle() const;
        
        string svgFooter() const;

        vector<Grid*> getGridNeighbours();

        int peutAvancerHorizontal(int i);

        bool operator==(const Grid& other) const;

        Grid operator=(const Grid& grid);

        bool isInNeighbours(Grid* grid) const;

        
};


#endif