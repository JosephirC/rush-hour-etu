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
        int exitPosX, exitPosY; // position de sortie
        vector<Car> carArray; // tableau des voitures de la grille
        int gridCarId[6][6]; // grille avec pour chaque case l'id de la voiture qui l'occupe
        Grid* parent;
        vector<Grid*> neighbours; // liste des voisins de cette grille
        string gridString; // cette grille sous forme de chaine de caractères (0015110320123 par exemple)

    public : 

        Grid();

        Grid(Grid& grid); // constructeur par copie

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

        string getGridString();
        
        Grid* getParent() const;

        void changeCarPosition(int id, int newPosX, int newPosY);

        vector<Car> getCarArray() const;

        void loadData(const string& filename);
        
        string svgHeader() const;

        string svgRectangle() const;
        
        string svgFooter() const;

        vector<Grid*> getGridNeighbours();

        bool isInNeighbours(Grid* grid) const;
        
};

#endif