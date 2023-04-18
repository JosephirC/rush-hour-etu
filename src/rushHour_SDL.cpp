#include "sdl.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

int main(int argc, char** argv){

    Grid grid(6,6);
    grid.initEmptyGrid();
    grid.loadData("./Sujet/puzzle.txt");

    SDL sj(grid);
	sj.sdlBoucle();

    return 0;
}