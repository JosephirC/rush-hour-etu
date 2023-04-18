#ifndef _SDL_HPP
#define _SDL_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "grid.hpp"

//! \brief Pour gérer une image avec SDL2
class Image {

private:

    /** < @param SDL_Surface m_surface Surface SDL */
    SDL_Surface * m_surface;
    
    /** @param SDL_Texture m_texture Texture SDL */
    SDL_Texture * m_texture;
    
    /** @param bool m_hasChanged Etat d'image */
    bool m_hasChanged;
    
    /** @param int nbrMoves Nombre de deplacements minimum pour gagner */
    int nbrMoves;

public:

    /** < @brief Constructeur d'Image */
    Image () ;

    /** < @brief Destructeur d'Image */
    ~Image();

    /**

    @brief Charge une image à partir d'un fichier.
    @param filename Le nom du fichier à charger.
    @param renderer Le SDL_Renderer sur lequel afficher l'image.
    */
    void loadFromFile (const char* filename, SDL_Renderer* renderer);


    void loadFromCurrentSurface (SDL_Renderer * renderer);
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
    SDL_Texture * getTexture() const;
    void setSurface(SDL_Surface * surf);

    /**
    @brief Detruit l'image courante pour charger l'image suivante.
    @param filename Le nom du fichier à charger.
    @param renderer Le SDL_Renderer sur lequel afficher l'image.
    */
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
