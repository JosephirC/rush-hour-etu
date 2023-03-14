#ifndef _SDL_HPP
#define _SDL_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "plateau.hpp"

struct Case {
    int x;
    int y;
};

//! \brief Pour gérer une image avec SDL2
class Image {

private:

    SDL_Surface * m_surface;
    SDL_Texture * m_texture;
    bool m_hasChanged;

public:
    Image () ;
    ~Image();
    void loadFromFile (const char* filename, SDL_Renderer * renderer);
    void loadFromCurrentSurface (SDL_Renderer * renderer);
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
    SDL_Texture * getTexture() const;
    void setSurface(SDL_Surface * surf);
};



/**
    La classe gerant le jeu avec un affichage SDL
*/
class SDL {

    private :

        //Jeu jeu;
        //Plateau p;

        SDL_Window * window;
        SDL_Renderer * renderer;

        TTF_Font * font;
        Image font_im;
        SDL_Color font_color;

        Mix_Chunk * sound;
        bool withSound;

        // Image im_pacman;
        // Image im_mur;
        // Image im_pastille;
        // Image im_fantome;
        Image im_voiture;

        vector<Voiture> tabVoitureGraphique;

        bool souris;
        bool touche;
        
    public :

        SDL ();
        ~SDL ();
        void sdlBoucle ();
        void sdlAff ();
        void drawMultipleHorLines(SDL_Renderer * renderer, int x, int y, int color, int gapSize);
        void drawMultipleVerLines(SDL_Renderer * renderer, int x, int y, int color, int gapSize);
        void copierTableau(vector<Voiture> tab);

};

#endif
