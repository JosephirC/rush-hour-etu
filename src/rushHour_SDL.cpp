#include "sdl.hpp"
#include "solver.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>

int main(int argc, char* argv[]){

    if (argc < 2) {
        std::cerr << endl << "Please specify an argument." << endl << "Choose the minimum number of moves to solve a puzzle." << std::endl;
        return 1;
    }

    int numberOfMoves = std::atoi(argv[1]);

    if(numberOfMoves < 3){
            std::cerr << endl << "Grids with " << numberOfMoves << " number of moves are too easy to solve.." << endl << "Please choose a positive number of moves higher than 3." << std::endl;
            return 1;
        }
    
    srand(time(0));

    Grid grid(6,6);
    grid.initEmptyGrid();
    grid.loadData("./Sujet/puzzle.txt");

    Solver solver(&grid);
    solver.setNbrOfMoves(numberOfMoves);
    SDL sj(grid, numberOfMoves);
	sj.sdlBoucle();

    return 0;
}