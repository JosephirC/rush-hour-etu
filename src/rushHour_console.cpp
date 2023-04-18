#include "car.hpp"
#include "grid.hpp"
#include "solver.hpp"
#include "puzzle.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <filesystem>

//#define GRID_DISPLAY
//#define LOAD_SVG
//#define GET_GRID_NEIGHBORS
//#define SOLVER_TEST
#define PUZZLE_TEST
//#define SOLVE_PROJECT

void generateLvl() {
    
   

}

int main(int argc, char* argv[]){

    srand(time(0));


    Grid grid(6,6);
    grid.initEmptyGrid();
    grid.loadData("./Sujet/puzzle.txt");

    #ifdef GRID_DISPLAY
    {
        cout << endl << "GRID_DISPLAY " << endl << endl;
        cout << "Je display les pos de sortie X : " << grid.getExitX() << " Y : " << grid.getExitY() << endl; 
        grid.displayCarArray();
        std::cout << "grille originale :" << std::endl;
        grid.displayGridId();
    }
    #endif

     #ifdef LOAD_SVG
    {
        cout << endl << "LOAD_SVG " << endl << endl;
        //Creation du .svg ---> Il faut faire une fonction pour cela !
        ofstream file("./images_svg/testSVG.svg");
        file << grid.svgHeader() << grid.svgRectangle() << grid.svgFooter(); 
    }
    #endif

    #ifdef GET_GRID_NEIGHBORS
    {
        cout << endl << "GET_GRID_NEIGHBORS " << endl << endl;
        vector<Grid*> test = grid.getGridNeighbours();
        for (int i=0; i<test.size(); i++) {
            std::cout << "grille voisine " << i << std::endl;
            test[i]->displayGridId();
        }
        cout << "taille du vector test " << test.size() << endl;
    }
    #endif  

    #ifdef SOLVER_TEST
    {
        cout << endl << "SOLVER_TEST " << endl << endl;
   
        Solver solution(&grid);
        solution.solve();

        //solution.solveTest();


        //vector<Grid*> winningGrids = solution.getWinningGrids();

        //cout << "wining size" << winningGrids.size() << endl;
        //cout << "covered size " << solution.getCoveredGrids().size() << endl;

        // for(int i =0; i < winningGrids.size(); i++){
        //     std::string filenumber = std::to_string(i);
        //     solution.solvedGridsSVG(winningGrids[i], filenumber);
        // }

        // solution.puzzle();

    }
    #endif

    #ifdef PUZZLE_TEST
    {
        if (argc < 2) {
            std::cerr << endl << "Please specify an argument." << endl << "Choose the minimum number of moves to solve a puzzle." << std::endl;
            return 1;
        }

        int numberOfMoves = std::atoi(argv[1]);

        if(numberOfMoves < 3){
            std::cerr << endl << "Grids with " << numberOfMoves << " number of moves are too easy to solve.." << endl << "Please choose a positive number of moves higher than 3." << std::endl;
            return 1;
        }

        Puzzle puzzle;
        Grid grid = puzzle.generateRandomGrid(6,12);

        Solver solver(&grid);
        int n = solver.solve();

        if (n == -1){
            std::cout << "Cette grille n'a pas de solution :/" << std::endl;
        }
        if (n == -2) {
            std::cout << "Le solveur prend trop de temps" << std::endl;
            std::cout << "Arret du programme..." << std::endl;
        }
        else if (n<=numberOfMoves && n >= 0) {
            std::cout << "La grille est trop facile..." << std::endl;
        }  
    }   
    #endif

    #ifdef SOLVE_PROJECT
    {
        cout << "SOLVE_PROJECT" << endl;

        Solver solution(&grid);
        solution.solve();
    }
    #endif

    return 0;
}
