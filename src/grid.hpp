#ifndef _PLATEAU_HPP
#define _PLATEAU_HPP

#include "voiture.hpp"
#include <iostream>
#include <vector>


using namespace std;

class Grid {
    private:
        const int MARGE = 20;
        const int TAILLE_CASE = 100;
        
        int width = 6;
        int length = 6;
        int endPosX, endPosY;
        vector<Voiture> carArray;
        int grilleIDCar[6][6]; // grille avec pour chaque case l'id de la voiture qui l'occupe

    public : 

    Grid();

    Grid(int sX, int sY);
    
    void initEmptyGrid();

    void displayGrid();

    void addCar(const Voiture& v);

    int getEndX() const;
    int getEndY() const;
    int getSizeX();
    int getSizeY();
    vector<Voiture> getCarArray();

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