#include "Plateau.hpp"
#include <iostream>

using namespace std;

Plateau::Plateau(){

}

void Plateau::afficherPlateau(){
    
    for(int i = 0; i < sizeX; i++){
        for(int j = 0; j < sizeY; j++){
            cout << ".";
        } cout << endl;
    }
    cout << endl;
}