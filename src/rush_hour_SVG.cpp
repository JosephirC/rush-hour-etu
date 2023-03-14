#include "car.hpp"
#include "grid.hpp"
#include "sdl.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char** argv){

    Grid p(6,6);
    //Voiture v(0, 0, 2, 1, 0);

    p.initEmptyGrid();
    //p.ajouterVoiture(v);
    p.loadData("./Sujet/puzzle.txt");


    cout << "Je display les pos de sortie X : " << p.getEndX() << " Y : " << p.getEndY() << endl; 
    p.displayCarArray();

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