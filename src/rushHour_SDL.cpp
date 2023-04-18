#include "sdl.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

int main(int argc, char* argv[]){

    srand(time(0));
    SDL sdl;
	sdl.sdlBoucle();

    return 0;
}