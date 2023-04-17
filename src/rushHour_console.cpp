#include "car.hpp"
#include "grid.hpp"
#include "solver.hpp"
#include "puzzle.hpp"
#include <iostream>
#include <fstream>
#include <string>


//#define CONSTRUCTOR_COPY
//#define GRID_DISPLAY
#define LOAD_SVG
//#define GET_GRID_NEIGHBORS
#define SOLVER_TEST
#define PUZZLE_TEST

int main(int argc, char** argv){

    Grid grid(6,6);
    grid.initEmptyGrid();
    grid.loadData("./Sujet/puzzle.txt");

    #ifdef CONSTRUCTOR_COPY
    {
        Grid grid1(grid);
        grid1.changeCarPosition(&grid1, 2, 3,2 );      
        grid1.displayGridId();

        cout<<"original grid display" << endl;
        grid.displayGridId();

        if(grid1 == grid){
            cout <<"nous sommes egale" << endl;
        }
        
        else {
            cout << "aie" << endl;
        }

        Grid grid2 = Grid(grid);
        if(grid2 == grid1)
            cout<<"2=0" << endl;


        Grid* gridPtr = &grid;

        cout<<"gridptr display" << endl;
        gridPtr->displayGridId();

        Grid* gridtest = new Grid(gridPtr);


        cout<<"gridtest display" << endl;
        gridtest->displayGridId();

        if(*gridtest== *gridPtr){
            cout <<"equals" << endl;
        }
        else {
            cout <<"bruh" << endl;
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
        ofstream file("./images_svg/testSVG.svg");
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
        cout << "taille du test " << test.size() << endl;
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
        Puzzle puzz;
        //puzz.generateRandomGrid(6, 13);
        //Grid puzz_test = puzz.getPuzzleGrid();
        //puzz_test.displayGridId();
        puzz.setNumberOfCars(puzz.randomNumberOfCars(6,13));
        puzz.generateRandomPuzzle();

    }   
    #endif

    return 0;
}
