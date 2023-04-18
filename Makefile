# L'inclusion ne change rien ? 
#DIR_SDL = -I /usr/include/SDL2
SDL_LIB = -lSDL2 -lSDL2_ttf -lSDL2_image

all: bin/rushHour_console bin/rushHour_SDL 

bin/rushHour_console: obj/rushHour_console.o obj/car.o obj/grid.o obj/solver.o obj/puzzle.o
	g++ -g obj/rushHour_console.o obj/car.o obj/grid.o obj/solver.o obj/puzzle.o -o bin/rushHour_console $(SDL_LIB)

bin/rushHour_SDL: obj/rushHour_SDL.o obj/car.o obj/grid.o obj/solver.o obj/puzzle.o obj/sdl.o
	g++ -g obj/rushHour_SDL.o obj/car.o obj/grid.o obj/solver.o obj/puzzle.o obj/sdl.o -o bin/rushHour_SDL $(SDL_LIB)

obj/rushHour_console.o: src/rushHour_console.cpp src/car.hpp src/grid.hpp src/solver.hpp src/puzzle.hpp
	g++ -g -c src/rushHour_console.cpp -o obj/rushHour_console.o $(DIR_SDL)

obj/rushHour_SDL.o: src/rushHour_SDL.cpp src/car.hpp src/grid.hpp src/solver.hpp src/puzzle.hpp src/sdl.hpp
	g++ -g -c src/rushHour_SDL.cpp -o obj/rushHour_SDL.o $(DIR_SDL)

obj/car.o: src/car.cpp
	g++ -g -c src/car.cpp -o obj/car.o $(DIR_SDL)

obj/grid.o: src/grid.cpp 
	g++ -g -c src/grid.cpp -o obj/grid.o $(DIR_SDL)

obj/solver.o: src/solver.cpp
	g++ -g -c src/solver.cpp -o obj/solver.o $(DIR_SDL)

obj/puzzle.o : src/puzzle.cpp
	g++ -g -c src/puzzle.cpp -o obj/puzzle.o $(DIR_SDL)

obj/sdl.o: src/sdl.cpp
	g++ -g -c src/sdl.cpp -o obj/sdl.o $(DIR_SDL)

clean:
	rm obj/*.o
	rm bin/*
	rm -rf images_svg/*