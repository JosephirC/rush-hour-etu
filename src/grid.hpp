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
        Grid* parent; // pointeur vers la grille parent de cette grille
        vector<Grid*> neighbours; // liste des voisins de cette grille
        string gridString; // cette grille sous forme de chaine de caractères (0015110320123 par exemple)

    public : 

        /** @brief Destructeur de Grid */
        ~Grid();

        /** @brief Constructeur de Grid */
        Grid();

        /** @brief Constructeur par copie de Grid
            @param const Grid& grid : grille à copier
        */
        Grid(const Grid& grid);

        /** @brief Constructeur de Grid avec des paramètres
            @param int _width : largeur de la grille
            @param int _height : hauteur de la grille
        */
        Grid(int _width, int _height);
        
        void initEmptyGrid();

        string gridToString();

        void addCar(const Car& v);

        void updateGridCarId(const vector<Car>& carArray);

        void displayGridId();

        int getExitX() const;

        int getExitY() const;

        int getSizeX() const;

        int getSizeY() const;

        void getGridCarId(int (&gridId)[6][6]);
        
        Grid* getParent() const;

        string getGridString();

        void setWidth(int w);

        void setHeight(int h);

        void setExitPosX(int eX);

        void setExitPosY(int eY);

        void setCarArray(vector<Car> car);

        void setParent(Grid* p);

        void setGridString(string s);

        void changeCarPosition(int id, int newPosX, int newPosY);

        vector<Car> getCarArray() const;

        void displayCarArray() const;

        void loadData(const string& filename);
        
        string svgHeader() const;

        string svgRectangle() const;
        
        string svgFooter() const;

        vector<Grid*> getGridNeighbours();

        // bool operator==(const Grid& other) const;

        Grid operator=(const Grid& grid);

        bool isInNeighbours(Grid* grid) const;
        
};

#endif