# L'inclusion ne change rien ? 
#DIR_SDL = -I /usr/include/SDL2
SDL_LIB = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

all: bin/rush_hour_SVG bin/rush_hour_SDL 

bin/rush_hour_SVG: obj/rush_hour_SVG.o obj/car.o obj/grid.o
	g++ -g obj/rush_hour_SVG.o obj/car.o obj/grid.o -o bin/rush_hour_SVG $(SDL_LIB)

bin/rush_hour_SDL: obj/rush_hour_SDL.o obj/car.o obj/grid.o obj/sdl.o
	g++ -g obj/rush_hour_SDL.o obj/car.o obj/grid.o obj/sdl.o -o bin/rush_hour_SDL $(SDL_LIB)

obj/rush_hour_SVG.o: src/rush_hour_SVG.cpp src/car.hpp src/grid.hpp
	g++ -g -c src/rush_hour_SVG.cpp -o obj/rush_hour_SVG.o $(DIR_SDL)

obj/rush_hour_SDL.o: src/rush_hour_SDL.cpp src/car.hpp src/grid.hpp src/sdl.cpp
	g++ -g -c src/rush_hour_SDL.cpp -o obj/rush_hour_SDL.o $(DIR_SDL)

obj/car.o: src/car.cpp
	g++ -g -c src/car.cpp -o obj/car.o $(DIR_SDL)

obj/grid.o: src/grid.cpp 
	g++ -g -c src/grid.cpp -o obj/grid.o $(DIR_SDL)

obj/sdl.o: src/sdl.cpp
	g++ -g -c src/sdl.cpp -o obj/sdl.o $(DIR_SDL)

clean:
	rm obj/*.o
	rm bin/*
	rm -rf images_svg/*