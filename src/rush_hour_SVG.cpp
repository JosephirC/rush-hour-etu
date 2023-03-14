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


    cout << "Je display les pos de sortie X : " << p.getExitX() << " Y : " << p.getExitY() << endl; 
    p.displayCarArray();
    p.displayGridId();

    //Creation du .svg ---> Il faut faire une fonction pour cela !
    ofstream file("./images_svg/image.svg");
    file << p.svgHeader() << p.svgRectangle() << p.svgFooter(); 


    return 0;
}