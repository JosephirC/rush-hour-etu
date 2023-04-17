#include <cassert>
#include <time.h>
#include "sdl.hpp"
#include <stdlib.h>
#include "grid.hpp"
#include "solver.hpp"
#include "puzzle.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <unistd.h>

#include <iostream>
using namespace std;

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

SDL_Texture * Image::getTexture() const {
    return m_texture;
}

void Image::setSurface(SDL_Surface * surf) {
    m_surface = surf;
}

// ============= CLASS SDLJEU =============== //

SDL::SDL (){

    SIZE_X = 600;
    SIZE_Y = 600;

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

    // Creation de la fenetre
    window = SDL_CreateWindow("RushHour", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SIZE_X, SIZE_Y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; 
        SDL_Quit(); 
        exit(1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

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


    //testLvl(grid);
}

SDL::~SDL () {
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDL::generateLvl() {
    // On reset le contenu du dossier images_svg
    std::filesystem::remove_all("./images_svg");
    std::filesystem::create_directory("./images_svg");

    Puzzle puzzle;
    Grid grid = puzzle.generateRandomGrid(6,13);

    Solver solver(&grid);
    int n = solver.solve();

    if (n==-1) {
        std::cout << "No solution to this grid :/" << std::endl;
        std::cout << "Generating new lvl..." << std::endl;
        sleep(1); 
        generateLvl();
    }
    if (n==-2) {
        std::cout << "Solver is taking too long, stoping..." << std::endl;
        std::cout << "Generating new lvl..." << std::endl;
        generateLvl();
    }
    else if (n<4-1) {
        std::cout << "Grid is too easy, generating new grid..." << std::endl;
        generateLvl();
    }

    nbImg = n;
    currentImg = n;
}

void SDL::loadGridImg(const string s) {
    if (s == "next" && (currentImg-1) > 0) {
        currentImg--;
    }
    else if (s == "previous" && (currentImg+1) <= nbImg) {
        currentImg++;
    }

    string path = "./images_svg/";
    path.append(std::to_string(currentImg)); // remplacer 15 par k
    path.append(".svg"); // remplacer 15 par k

    char* char_path = new char[path.length() + 1];
    strcpy(char_path, path.c_str());

    gridImg.loadFromFile(char_path, renderer);
    imgSet = true; 

    delete char_path;
}


void SDL::sdlAff () {
	//Remplir l'écran de noir
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    // dessiner la grille si elle a été chargée
    if (imgSet) {
        gridImg.draw(renderer, 100,100,400,400);
    }

    // Ecrire un titre par dessus
    SDL_Rect positionTitre = {250,25,100,30};
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTitre);

}

void SDL::sdlBoucle () {
    SDL_Event events;
	bool quit = false;

    Uint32 t = SDL_GetTicks(), nt;

	// tant que ce n'est pas la fin
	while (!quit) {

        nt = SDL_GetTicks();
        if (nt-t>500) {
            t = nt;
        }

		// tant qu'il y a des évenements à traiter
		while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT) quit = true;           
			else if (events.type == SDL_KEYDOWN) {          
				switch (events.key.keysym.scancode) {
				case SDL_SCANCODE_UP:
                    generateLvl();
					break;
                case SDL_SCANCODE_DOWN:
					loadGridImg("");
					break;
                case SDL_SCANCODE_RIGHT:
                    loadGridImg("next");
					break;
                case SDL_SCANCODE_LEFT:
                    loadGridImg("previous");
					break;
                case SDL_SCANCODE_ESCAPE:
                    quit = true;
                    break;
				default: break;
				}

			}
		}

		// on affiche le jeu
		sdlAff();
        SDL_RenderPresent(renderer);
	}
}
