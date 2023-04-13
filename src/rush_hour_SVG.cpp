#include "car.hpp"
#include "grid.hpp"
#include "solver.hpp"
//#include "sdl.hpp"
#include <iostream>
#include <fstream>


#define CONSTRUCTOR_COPY
#define GRID_DISPLAY
#define LOAD_SVG
#define GET_NEIGHBORD_CARS
#define SOLVER_TEST

int main(int argc, char** argv){

    Grid grid(6,6);
    //Voiture v(0, 0, 2, 1, 0);

    grid.initEmptyGrid();
    //g.ajouterVoiture(v);
    grid.loadData("./Sujet/puzzle.txt");


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
    ofstream file("./images_svg/original.svg");
    file << grid.svgHeader() << grid.svgRectangle() << grid.svgFooter(); 


    #ifdef SOLVER_TEST
    {
        Solver sol(&grid);
        sol.solve1();
        cout << "le solver fonctionne ? " << endl;
    }
    #endif

    return 0;
}