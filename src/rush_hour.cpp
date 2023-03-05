#include "voiture.hpp"
#include "plateau.hpp"
#include "sdl.hpp"
#include <iostream>


// #include <SDL2/SDL.h>
// #include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_mixer.h>


using namespace std;

int main() {

    Plateau p;

    p.afficherPlateau();

    SDL sj;
	sj.sdlBoucle();
	return 0;

   

    return 0;
}