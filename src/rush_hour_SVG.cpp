#include "voiture.hpp"
#include "plateau.hpp"
#include "sdl.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char** argv){

    Plateau p(6,6);
    //Voiture v(0, 0, 2, 1, 0);

    p.initPlateauVide();
    //p.ajouterVoiture(v);
    p.ChargerDonnees("./Sujet/puzzle.txt");


    cout << "Je display les pos de sortie X : " << p.getSortieX() << " Y : " << p.getSortieY() << endl; 
    p.affichageTabVoiture();

    p.HeaderSVG();
    p.RectangleSVG();
    p.FooterSVG();

    //Creation du .svg ---> Il faut faire une fonction pour cela !
    ofstream file("./images_svg/image.svg");
    file << p.HeaderSVG() << p.RectangleSVG() << p.FooterSVG(); 

    /**************NE PAS DECOMMENTER****************/
            //p.ToSVG(v, p, "image1.svg");
    /************************************************/

    return 0;
}