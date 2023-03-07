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
        int grilleIDVoiture[6][6]; // grille avec pour chaque case l'id de la voiture qui l'occupe

    public : 

    Plateau();

    Plateau(int sX, int sY);
    
    void initPlateauVide();

    void afficherPlateau();

    void ajouterVoiture(const Voiture& v);

    int getSortieX() const;
    int getSortieY() const;
    int getTailleX();
    int getTailleY();
    vector<Voiture> getTabVoiture();

    void affichageTabVoiture();

    void ToSVG(const Voiture& v, const Plateau& p, const char* filename);

    string ToSVG(const Plateau& p, const Voiture& v) const;

    void ChargerDonnees(const string& filename);
    
    string HeaderSVG(const Plateau& p) const;

    string RectangleSVG(const Plateau& p) const;
    
    string FooterSVG() const;
};
#endif