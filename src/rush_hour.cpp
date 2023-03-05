#include "voiture.hpp"
#include "plateau.hpp"
#include "sdl.hpp"
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

SDL_Event event;
bool quit = false;

int main(int argc, char** argv){

    Plateau p;

    // /* Initialisation simple */
    // if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    // {
    //     fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
    //     return -1;
    // }

    
    //     SDL_Window* pWindow = NULL;
    //     pWindow = SDL_CreateWindow("RushHour",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

    //     if(pWindow)
    //     {
    //         while(quit == false) {
    //             while( SDL_PollEvent(&event)) {
    //                 if(event.type==SDL_QUIT) {
    //                     quit = true;
    //                 }    
    //             }
    //         }
    //     }

    p.afficherPlateau();

    SDL sj;
	sj.sdlBoucle();


    return 0;
}