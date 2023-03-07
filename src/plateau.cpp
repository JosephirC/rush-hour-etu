#include "plateau.hpp"
#include <iostream>

using namespace std;

Plateau::Plateau(int sX, int sY) :
sizeX(6),
sizeY(6)
{
    sizeX = sX;
    sizeY = sY;
}

void Plateau:: initPlateauVide(){
    
    for(int i = 0; i < sizeX; i++){
        for(int j = 0; j < sizeY; j++){
            cout << ".";
        } cout << endl;
    }
    cout << endl;
}

void Plateau::ajouterVoiture(const Voiture& v){
    tabVoiture.push_back(v);
}

string Plateau:: ToSVG() const {
    return " ";
}