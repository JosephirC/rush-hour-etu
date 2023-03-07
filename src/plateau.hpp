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
        int sortiePosX, sortiePosY;
        vector<Voiture> tabVoiture;

    public : 

    Plateau(int sX, int sY);
    
    void initPlateauVide();

    void ajouterVoiture(const Voiture& v);

    int getSortieX() const;
    
    int getSortieY() const;

    void affichageTabVoiture();

    void ToSVG(const Voiture& v, const Plateau& p, const char* filename);

    string ToSVG(const Plateau& p, const Voiture& v) const;

    void ChargerDonnees(const string& filename);
    
    string HeaderSVG() const;

    string RectangleSVG() const;
    
    string FooterSVG() const;
};
#endif