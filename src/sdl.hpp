#ifndef _SDL_HPP
#define _SDL_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "grid.hpp"

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

        // taille de la fenetre
        int SIZE_X;
        int SIZE_Y;

        SDL_Window * window;
        SDL_Renderer * renderer;

        TTF_Font * font;
        Image font_im;
        SDL_Color font_color;

        //Image im_car;

        Image gridImg;

        //Grid grid;

        bool souris;
        bool touche;
        bool pressed = false; // si une touche est appuyée

        bool imgSet = false;
        int nbImg;
        int currentImg;

        bool stopSolve;
        
    public :

        SDL ();
        ~SDL ();
        void sdlBoucle ();
        void sdlAff ();
        void generateLvl();
        void loadGridImg(const string c);

};

#endif
