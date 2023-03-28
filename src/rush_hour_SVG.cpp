#include "car.hpp"
#include "grid.hpp"
#include "sdl.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char** argv){

    Grid grid(6,6);
    //Voiture v(0, 0, 2, 1, 0);

    grid.initEmptyGrid();
    //g.ajouterVoiture(v);
    grid.loadData("./Sujet/puzzle.txt");


    cout << "Je display les pos de sortie X : " << grid.getExitX() << " Y : " << grid.getExitY() << endl; 
    grid.displayCarArray();
    grid.displayGridId();

    //Creation du .svg ---> Il faut faire une fonction pour cela !
    ofstream file("./images_svg/image.svg");
    file << grid.svgHeader() << grid.svgRectangle() << grid.svgFooter(); 


    //test neighbor function
    vector<int> test = grid.getNeighborCars(2);

    for(int i = 0; i <test.size(); i++){
        cout << "neighbor id is " << test[i] << endl;
    }


    return 0;
}