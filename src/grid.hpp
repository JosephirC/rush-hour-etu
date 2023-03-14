#ifndef _PLATEAU_HPP
#define _PLATEAU_HPP

#include "car.hpp"
#include <iostream>
#include <vector>


using namespace std;




/**********==NOTES==********/
/*
STOCKER LES CASES VIDES DANS LA DIRECTION D'UNE VOITURE POUR VOIR DE COMBIEN DE CASES ELLE PEUT AVANCER
cOMPTER LE NOMBRE DE DEPLACEMENT DE VOITURE --> SCORE

FONCTION POUR CHERCHER LES VOITURES VOISINES

FONCTION POUR DEPLACER LES VOITURE(QUI PEUVENT SE DEPLACER) DE UN SEUL COUP 


*/


class Grid {
    private:
        const int MARGE = 20;
        const int TAILLE_CASE = 100;
        
        int width = 6;
        int length = 6;
        int endPosX, endPosY;
        vector<Car> carArray;
        int grilleIDCar[6][6]; // grille avec pour chaque case l'id de la voiture qui l'occupe

    public : 

    Grid();

    Grid(int sX, int sY);
    
    void initEmptyGrid();

    void displayGrid();

    void addCar(const Car& v);

    int getEndX() const;
    int getEndY() const;
    int getSizeX();
    int getSizeY();
    vector<Car> getCarArray();

    void displayCarArray();

    //Utiliser ofstream ou string stream ??? Difference ?
    //reponse : utiliser un string stream pour pouvoir forger les differents svg
    void loadData(const string& filename);
    
    string HeaderSVG() const;

    string RectangleSVG() const;
    
    string FooterSVG() const;

    void addGameSituation();
};
#endif