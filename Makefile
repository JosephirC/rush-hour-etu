DIR_SDL = -I /usr/include/SDL2
SDL_LIB = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

all: bin/rush_hour

bin/rush_hour: obj/rush_hour.o obj/voiture.o obj/plateau.o
	g++ obj/rush_hour.o obj/voiture.o obj/plateau.o -o bin/rush_hour $(SDL_LIB)

obj/rush_hour.o: src/rush_hour.cpp src/voiture.hpp src/plateau.hpp
	g++ -ggdb -Wall -c src/rush_hour.cpp -o obj/rush_hour.o $(DIR_SDL)

obj/voiture.o: src/voiture.cpp
	g++ -ggdb -Wall -c src/voiture.cpp -o obj/voiture.o $(DIR_SDL)

obj/plateau.o: src/plateau.cpp 
	g++ -ggdb -Wall -c src/plateau.cpp -o obj/plateau.obj $(DIR_SDL)

clean:
	rm obj/*.o
	rm bin/*