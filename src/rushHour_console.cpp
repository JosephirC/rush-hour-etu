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


bool solveLvl(Grid grid) {
    Solver solver(&grid);
    int n = solver.solve();

    if (n==-1) {
        std::cout << "Cette grille n'a pas de solution :/" << std::endl;
        std::cout << "Generation d'un nouveau niveau..." << std::endl;
        return false;
    }
    if (n==-2) {
        std::cout << "Le solveur prend trop de temps, generation d'un nouveau niveau..." << std::endl;
        return false;
    }
    else if (n<3) {
        std::cout << "La grille est trop facile, generation d'un nouveau niveau..." << std::endl;
        return false;
    }
    else {
        return true;
    }   
}

void generateLvl() {
    
    Puzzle puzzle;
    Grid grid = puzzle.generateRandomGrid(6,12);

    while (!(solveLvl(grid))) {
        generateLvl();
    }

}

int main(int argc, char* argv[]){

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

        if(numberOfMoves < 4){
            std::cerr << endl << "Grids with " << numberOfMoves << " number of moves are too easy to solve.." << endl << "Please choose a positive number of moves higher than 3." << std::endl;
            return 1;
        }

        srand(time(0));
        generateLvl();
        // Puzzle puzzle;
        // puzzle.makeEmptyGrid();
        // Grid grid = puzzle.getPuzzleGrid();
        // puzzle.generateRandomGrid(11,13);
        
        // grid = puzzle.getPuzzleGrid();

        // Solver solver(&grid);

        // solver.setNbrOfMoves(numberOfMoves);

        // int i = solver.solve();
    
        // if( i== -1){
        //     cout << "pas de solution " << endl;
        // }

        // if (i == -2) {
        //     std::cout << endl << "Solver is taking too long, stoping..." << std::endl;
        //     std::cout << "Generating new lvl..." << std::endl;
        //     //sleep(2);

        //     // On reset le contenu du dossier images_svg
        //     std::filesystem::remove_all("./images_svg");
        //     std::filesystem::create_directory("./images_svg");

        //     puzzle.generateRandomGrid(11,13);
        // }

        // if(i < numberOfMoves){
        //     std::cout << "Grid is too easy, generating new grid..." << std::endl;
        //     //sleep(2);
        //     puzzle.generateRandomGrid(11,13);
        // }

    



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
