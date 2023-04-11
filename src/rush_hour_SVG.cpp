#include "car.hpp"
#include "grid.hpp"
//#include "sdl.hpp"
#include <iostream>
#include <fstream>

#define CONSTRUCTOR_COPY
#define GRID_DISPLAY
#define LOAD_SVG
#define GET_NEIGHBORD_CARS

int main(int argc, char** argv){

    Grid grid(6,6);
    //Voiture v(0, 0, 2, 1, 0);

    grid.initEmptyGrid();
    //g.ajouterVoiture(v);

    #ifdef CONSTRUCTOR_COPY
    {

        Grid grid1(grid);

        if(grid1 == grid){
            cout <<"nous sommes egale" << endl;
        }
    }
    #endif


    cout << "Je display les pos de sortie X : " << grid.getExitX() << " Y : " << grid.getExitY() << endl; 
    grid.displayCarArray();
    std::cout << "grille originale :" << std::endl;
    grid.displayGridId();

    //Creation du .svg ---> Il faut faire une fonction pour cela !
    ofstream file("./images_svg/image.svg");
    file << grid.svgHeader() << grid.svgRectangle() << grid.svgFooter(); 

    vector<Grid*> test = grid.getGridNeighbours();

    for (int i=0; i<test.size(); i++) {
        std::cout << "grille voisine " << i << std::endl;
        test[i]->displayGridId();
    }

    #ifdef LOAD_SVG
    {
        //Creation du .svg ---> Il faut faire une fonction pour cela !
        ofstream file("./images_svg/image.svg");
        file << grid.svgHeader() << grid.svgRectangle() << grid.svgFooter(); 
    }
    #endif

    // vector<Grid> test = grid.getGridNeighbours();

    // for (int i=0; i<test.size(); i++) {
    //     std::cout << "grille " << i << std::endl;
    //     test[i].displayGridId();
    // }


    #ifdef GET_NEIGHBORD_CARS
    {
        //test neighbor function
        int carId = 0;
        vector<int> test;

        for(int i = 0; i < grid.getCarArray().size(); i++){
            cout << "Working on Car id : " << carId << endl;
            test =  grid.getNeighboursCars(carId);
            carId++;
            cout << endl;
        }
    }
    #endif

    
    return 0;
}