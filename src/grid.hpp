#ifndef _PLATEAU_HPP
#define _PLATEAU_HPP

#include "car.hpp"
#include <iostream>
#include <vector>


using namespace std;




/**********==NOTES==********/
/*
STOCKER LES CASES VIDES DANS LA DIRECTION D'UNE VOITURE POUR VOIR DE COMBIEN DE CASES ELLE PEUT AVANCER
COMPTER LE NOMBRE DE DEPLACEMENT DE VOITURE --> SCORE

FONCTION POUR CHERCHER LES VOITURES VOISINES

FONCTION POUR DEPLACER LES VOITURE(QUI PEUVENT SE DEPLACER) DE UN SEUL COUP 


*/


class Grid {
    private:
        const int MARGE = 20;
        const int TAILLE_CASE = 100;
        
        int width = 6;
        int height = 6;
        int exitPosX, exitPosY;
        vector<Car> carArray;
        int gridCarId[6][6]; // grille avec pour chaque case l'id de la voiture qui l'occupe

    public : 

        Grid();

        Grid(int sX, int sY);
        
        void initEmptyGrid();

        void addCar(const Car& v);

        void displayGridId();

        int getExitX() const;

        int getExitY() const;

        int getSizeX() const;

        int getSizeY() const;

        vector<Car> getCarArray();

        void displayCarArray();

        //Utiliser ofstream ou string stream ??? Difference ?
        //reponse : utiliser un string stream pour pouvoir forger les differents svg
        void loadData(const string& filename);
        
        string svgHeader() const;

        string svgRectangle() const;
        
        string svgFooter() const;

        void addGameSituation();

        vector<int> getNeighborCars(int carId);

        
};
#endif