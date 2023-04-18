#ifndef _SDL_HPP
#define _SDL_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "grid.hpp"

//! \brief Pour gérer une image avec SDL2
class Image {

private:

    /** @param SDL_Surface m_surface Surface SDL **/
    SDL_Surface * m_surface;
    
    /** @param SDL_Texture m_texture Texture SDL **/
    SDL_Texture * m_texture;
    
    /** @param bool m_hasChanged Etat d'image **/
    bool m_hasChanged;
    
    
    int nbrMoves;

public:

    /** @brief Constructeur d'Image **/
    Image () ;


    /** @brief Destructeur d'Image **/
    ~Image();


    /** 
     * @brief Charge une image à partir d'un fichier.
     * @param filename Le nom du fichier à charger.
     * @param renderer Le SDL_Renderer sur lequel afficher l'image.
    **/
    void loadFromFile (const char* filename, SDL_Renderer* renderer);


    /**
     * @brief Charge une texture SDL à partir de la surface courante de l'objet.
     * @param renderer Le SDL_Renderer sur lequel charger la texture.
     **/
    void loadFromCurrentSurface (SDL_Renderer * renderer);


    /** 
     * @brief Affiche l'objet sur le renderer aux coordonnées spécifiées.
     * @param renderer Le SDL_Renderer sur lequel afficher l'objet.
     * @param x La position horizontale de l'objet sur le rendu.
     * @param y La position verticale de l'objet sur le rendu.
     * @param w La largeur de l'objet à afficher, ou -1 pour conserver la taille originale.
     * @param h La hauteur de l'objet à afficher, ou -1 pour conserver la taille originale.
    **/
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
    

    /** @brief Renvoie la texture SDL de l'objet. **/
    SDL_Texture * getTexture() const;


    /**
     * @brief Modifie la surface courante de l'objet.\
     * @param surf La nouvelle surface à utiliser pour l'objet.
    **/
    void setSurface(SDL_Surface * surf);


    /**
     * @brief Detruit l'image courante pour charger l'image suivante.
     * @param filename Le nom du fichier à charger.
     * @param renderer Le SDL_Renderer sur lequel afficher l'image.
    */
    void checkFrees();
};


/**
    La classe gerant l'affichage SDL
*/
class SDL {

    private :

        /** @param int SIZE_X Largeur de la fenetre **/
        int SIZE_X;

        /** @param int SIZE_Y Hauteur de la fenetre **/
        int SIZE_Y;


        /** @param SDL_Window* window La fenêtre SDL utilisée pour afficher le contenu graphique.**/
        SDL_Window* window;

        /** @param SDL_Renderer* renderer Le rendu SDL utilisé pour dessiner les éléments graphiques **/
        SDL_Renderer* renderer;


        /** @param TTF_Font* font La police TTF utilisée pour afficher du texte **/
        TTF_Font* font;

        /** @param Image font_im L'image utilisée pour afficher le texte avec la police TTF **/
        Image font_im;

        /** @param SDL_Color font_color La couleur du texte à afficher avec la police TTF **/
        SDL_Color font_color;


        /** @param Image gridImg Pour affichier l'image SVG de la grille sur SDL **/
        Image gridImg;

        /** @param bool imgSet Pour verifier si l'image est valide **/
        bool imgSet = false;

        /** @param int nbImg Pour savoir le nombre d'image a afficher **/
        int nbImg;

        /** @param int currentImg Pour savoir quelle est l'image courante **/
        int currentImg;

        /** @param int nbMoves Nombre de deplacements minimum pour gagner **/
        int nbMoves;
                
    public :

        /** 
         * @brief Constructeur SDL qui prend une grille et le nombre de mouvement minimum pour resoudre la grille en parametre
         * @param Grid grid La grille qu'on veut afficher sur SDL
         * @param int nbM Le nombre de mouvement minimum pour resoudre la grille
        **/
        SDL (Grid grid, int nbM);

        /** @brief Destructeur SDL **/
        ~SDL ();

        /** @brief Boucle SDL **/
        void sdlBoucle ();

        /** @brief  Contient tous les affichages SDL **/
        void sdlAff ();

        /** @brief Generation d'un niveau **/
        void generateLvl();

        /** 
         * @brief Resolution de la grille sur SDL
         * @param Grid grid grille a resoudre
        **/
        void solveLvl(Grid grid);

        /** 
         * @brief Permet de naviguer les images qu'on a generer pour une grille
         * @param const string c Pour afficher l'image precedente et suivante **/
        void loadGridImg(const string c);
};
#endif