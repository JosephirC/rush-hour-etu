#include "sdl.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

SDL_Event event;
bool quit = false;

int main(int argc, char** argv){

    Grid p(6,6);
    //Voiture v(0, 0, 2, 1, 0);

    p.initEmptyGrid();
    //p.ajouterVoiture(v);
    p.loadData("./Sujet/puzzle.txt");

    SDL sj;
	sj.sdlBoucle();


    return 0;


}