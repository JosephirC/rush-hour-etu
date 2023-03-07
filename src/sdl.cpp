#include <cassert>
#include <time.h>
#include "sdl.hpp"
#include <stdlib.h>

#include <iostream>
using namespace std;

const int TAILLE_SPRITE = 32;

float temps () {
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC;  // conversion des ms en secondes en divisant par 1000
}

// ============= CLASS IMAGE =============== //

Image::Image () : m_surface(nullptr), m_texture(nullptr), m_hasChanged(false) {
}

Image::~Image()
{
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);

    m_surface = nullptr;
    m_texture = nullptr;
    m_hasChanged = false;
}

void Image::loadFromFile (const char* filename, SDL_Renderer * renderer) {
    m_surface = IMG_Load(filename);
    if (m_surface == nullptr) {
        string nfn = string("../") + filename;
        cout << "Error: cannot load "<< filename <<". Trying "<<nfn<<endl;
        m_surface = IMG_Load(nfn.c_str());
        if (m_surface == nullptr) {
            nfn = string("../") + nfn;
            m_surface = IMG_Load(nfn.c_str());
        }
    }
    if (m_surface == nullptr) {
        cout<<"Error: cannot load "<< filename <<endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(m_surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(m_surface);
    m_surface = surfaceCorrectPixelFormat;

    m_texture = SDL_CreateTextureFromSurface(renderer,surfaceCorrectPixelFormat);
    if (m_texture == NULL) {
        cout << "Error: problem to create the texture of "<< filename<< endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::loadFromCurrentSurface (SDL_Renderer * renderer) {
    m_texture = SDL_CreateTextureFromSurface(renderer,m_surface);
    if (m_texture == nullptr) {
        cout << "Error: problem to create the texture from surface " << endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::draw (SDL_Renderer * renderer, int x, int y, int w, int h) {
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w<0)?m_surface->w:w;
    r.h = (h<0)?m_surface->h:h;

    if (m_hasChanged) {
        ok = SDL_UpdateTexture(m_texture,nullptr,m_surface->pixels,m_surface->pitch);
        assert(ok == 0);
        m_hasChanged = false;
    }

    ok = SDL_RenderCopy(renderer,m_texture,nullptr,&r);
    assert(ok == 0);
}

SDL_Texture * Image::getTexture() const {return m_texture;}

void Image::setSurface(SDL_Surface * surf) {m_surface = surf;}





// Variables globales images
Image im_car2_main;


// ============= CLASS SDLJEU =============== //

SDL::SDL (){
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        cout << "No sound !!!" << endl;
        //SDL_Quit();exit(1);
        withSound = false;
    }
    else withSound = true;


    // Creation de la fenetre
    window = SDL_CreateWindow("RushHour", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; 
        SDL_Quit(); 
        exit(1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    // IMAGES
    im_car2_main.loadFromFile("images/car2_main.png", renderer);
    

    // FONTS
    font = TTF_OpenFont("data/DejaVuSansCondensed.ttf",50);
    if (font == nullptr)
        font = TTF_OpenFont("../data/DejaVuSansCondensed.ttf",50);
    if (font == nullptr) {
            cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: " << TTF_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}
    font_color = {250,250,250};
	font_im.setSurface(TTF_RenderText_Solid(font,"Niveau 1",font_color));
	font_im.loadFromCurrentSurface(renderer);

    // SONS
    if (withSound)
    {
        // sound = Mix_LoadWAV("data/son.wav");
        // if (sound == nullptr) 
        //     sound = Mix_LoadWAV("../data/son.wav");
        // if (sound == nullptr) {
        //         cout << "Failed to load son.wav! SDL_mixer Error: " << Mix_GetError() << endl; 
        //         SDL_Quit();
        //         exit(1);
        // }
    }
}

SDL::~SDL () {
    if (withSound) Mix_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDL::drawMultipleHorLines(SDL_Renderer * renderer, int x, int y, int color, int gapSize) {
    SDL_SetRenderDrawColor(renderer, color, color, color, 255);
    for (int i =0; i<6; i++) {
        SDL_RenderDrawLine(renderer,x,y,x+gapSize,y);
        x += gapSize;
    }
}

void SDL::drawMultipleVerLines(SDL_Renderer * renderer, int x, int y, int color, int gapSize) {
    SDL_SetRenderDrawColor(renderer, color, color, color, 255);
    for (int i =0; i<6; i++) {
        SDL_RenderDrawLine(renderer,x,y,x,y+gapSize);
        y += gapSize;
    }
}

void SDL::sdlAff () {
	//Remplir l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    // Grille
    int x, y;

    x = 132;
    for (int i =0; i<6; i++) {
        drawMultipleVerLines(renderer,x,76,60,84);
        x += 84;
    }  

    y = 160;
    for (int i =0; i<6; i++) {
        drawMultipleHorLines(renderer,48,y,60,84);
        y += 84;
    }

    // Bordures
    drawMultipleHorLines(renderer,48,76,255,84);
    drawMultipleHorLines(renderer,48,580,255,84);
    drawMultipleVerLines(renderer,48,76,255,84);
    drawMultipleVerLines(renderer,552,76,255,84);


    im_car2_main.draw(renderer, 216, 160, 83, 166);

    // Ecrire un titre par dessus
    SDL_Rect positionTitre = {250,25,100,30};
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTitre);

}

void SDL::sdlBoucle () {
    SDL_Event events;
	bool quit = false;

    Uint32 t = SDL_GetTicks(), nt;

	// tant que ce n'est pas la fin ...
	while (!quit) {

        nt = SDL_GetTicks();
        if (nt-t>500) {
            //jeu.actionsAutomatiques();
            t = nt;
        }

		// tant qu'il y a des évenements à traiter (cette boucle n'est pas bloquante)
		while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT) quit = true;           // Si l'utilisateur a clique sur la croix de fermeture
			else if (events.type == SDL_KEYDOWN) {              // Si une touche est enfoncee
                bool mangePastille = false;
				switch (events.key.keysym.scancode) {
				case SDL_SCANCODE_UP:
					//mangePastille = jeu.actionClavier('b');    // car Y inverse
					break;
                case SDL_SCANCODE_ESCAPE:
                    quit = true;
                    break;
				default: break;
				}
				if ((withSound) && (mangePastille))
                    Mix_PlayChannel(-1,sound,0);
			}
		}

		// on affiche le jeu sur le buffer cach�
		sdlAff();

		// on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
	}
}
