# L'inclusion ne change rien ? 
#DIR_SDL = -I /usr/include/SDL2
SDL_LIB = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

all: bin/rush_hour_SVG bin/rush_hour_SDL 

bin/rush_hour_SVG: obj/rush_hour_SVG.o obj/voiture.o obj/grid.o
	g++ obj/rush_hour_SVG.o obj/voiture.o obj/grid.o -o bin/rush_hour_SVG $(SDL_LIB)

bin/rush_hour_SDL: obj/rush_hour_SDL.o obj/voiture.o obj/grid.o obj/sdl.o
	g++ obj/rush_hour_SDL.o obj/voiture.o obj/grid.o obj/sdl.o -o bin/rush_hour_SDL $(SDL_LIB)

obj/rush_hour_SVG.o: src/rush_hour_SVG.cpp src/voiture.hpp src/grid.hpp
	g++ -c src/rush_hour_SVG.cpp -o obj/rush_hour_SVG.o $(DIR_SDL)

obj/rush_hour_SDL.o: src/rush_hour_SDL.cpp src/voiture.hpp src/grid.hpp src/sdl.cpp
	g++ -c src/rush_hour_SDL.cpp -o obj/rush_hour_SDL.o $(DIR_SDL)

obj/voiture.o: src/voiture.cpp
	g++ -c src/voiture.cpp -o obj/voiture.o $(DIR_SDL)

obj/grid.o: src/grid.cpp 
	g++ -c src/grid.cpp -o obj/grid.o $(DIR_SDL)

obj/sdl.o: src/sdl.cpp
	g++ -c src/sdl.cpp -o obj/sdl.o $(DIR_SDL)

clean:
	rm obj/*.o
	rm bin/*
	rm images_svg/*