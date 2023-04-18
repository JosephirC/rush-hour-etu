#ifndef _SDL_HPP
#define _SDL_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "grid.hpp"

//! \brief Pour gérer une image avec SDL2
class Image {

private:

    SDL_Surface * m_surface;
    SDL_Texture * m_texture;
    bool m_hasChanged;
    int nbrMoves;

public:
    Image () ;
    ~Image();
    void loadFromFile (const char* filename, SDL_Renderer * renderer);
    void loadFromCurrentSurface (SDL_Renderer * renderer);
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
    SDL_Texture * getTexture() const;
    void setSurface(SDL_Surface * surf);
    void checkFrees();
};



/**
    La classe gerant l'affichage SDL
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

        Image gridImg;

        bool imgSet = false;
        int nbImg;
        int currentImg;

        int nbMoves;

        Grid gridTest;
        
    public :

        SDL (Grid grid, int nbM);
        ~SDL ();
        void sdlBoucle ();
        void sdlAff ();
        void generateLvl();
        void solveLvl(Grid grid);
        void loadGridImg(const string c);
};

#endif
