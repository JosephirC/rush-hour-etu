#ifndef _PLATEAU_HPP
#define _PLATEAU_HPP

#include "voiture.hpp"
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


class Plateau {
    private:
        const int MARGE = 20;
        const int TAILLE_CASE = 100;
        
        int largeur = 6;
        int longueur = 6;
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

    //Utiliser ofstream ou string stream ??? Difference ?
    //reponse : utiliser un string stream pour pouvoir forger les differents svg
    void ChargerDonnees(const string& filename);
    
    string HeaderSVG() const;

    string RectangleSVG() const;
    
    string FooterSVG() const;
};
#endif