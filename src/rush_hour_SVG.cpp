#include "car.hpp"
#include "grid.hpp"
#include "solver.hpp"
//#include "sdl.hpp"
#include <iostream>
#include <fstream>


//#define CONSTRUCTOR_COPY
//#define GRID_DISPLAY
//#define LOAD_SVG
//#define GET_GRID_NEIGHBORS
#define SOLVER_TEST

int main(int argc, char** argv){

    Grid grid(6,6);
    //Voiture v(0, 0, 2, 1, 0);

    grid.initEmptyGrid();
    //g.ajouterVoiture(v);
    grid.loadData("./Sujet/puzzle.txt"); //pk j'ai 50 fils quand je le mets dans le constructeur *_*

    #ifdef CONSTRUCTOR_COPY
    {

        Grid grid1(grid);

        if(grid1 == grid){
            cout <<"nous sommes egale" << endl;
        }
    }
    #endif

    #ifdef GRID_DISPLAY
    {
        cout << "Je display les pos de sortie X : " << grid.getExitX() << " Y : " << grid.getExitY() << endl; 
        grid.displayCarArray();
        std::cout << "grille originale :" << std::endl;
        grid.displayGridId();
    }
    #endif

    #ifdef LOAD_SVG
    {
        //Creation du .svg ---> Il faut faire une fonction pour cela !
        ofstream file("./images_svg/image.svg");
        file << grid.svgHeader() << grid.svgRectangle() << grid.svgFooter(); 
    }
    #endif


    #ifdef GET_GRID_NEIGHBORS
    {
        vector<Grid*> test = grid.getGridNeighbours();
        for (int i=0; i<test.size(); i++) {
            std::cout << "grille voisine " << i << std::endl;
            test[i]->displayGridId();
        }
    }
    #endif

    #ifdef SOLVER_TEST
    {
        cout << endl << "SOLVER_TEST " << endl << endl;
        
        Solver sol(&grid);
        sol.solve1();
        sol.solvedGridsSVG();
        vector<Grid*> coveredGrid = sol.getCoveredGrids();
        cout << "size:"  << coveredGrid.size()<<endl;

        for(int i = 0; i < coveredGrid.size(); i++){
            coveredGrid[i]->displayGridId();
        }
        sol.solvedGridsSVG();
    }
    #endif

    return 0;
}