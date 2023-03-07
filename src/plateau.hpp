#ifndef _PLATEAU_HPP
#define _PLATEAU_HPP

#include "voiture.hpp"
#include <iostream>
#include <vector>


using namespace std;

class Plateau {
    private:
        int sizeX = 6;
        int sizeY = 6;
        vector<Voiture> tabVoiture;

    public : 

    Plateau(int sX, int sY);
    
    void initPlateauVide();

    void ajouterVoiture(const Voiture& v);

    string ToSVG() const;
};
#endif