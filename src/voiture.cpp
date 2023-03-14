#include "voiture.hpp"

Voiture:: Voiture(int _posX, int _posY, int _taille, int _direction, int _id){
    posX = _posX;
    posY = _posY;
    taille = _taille;
    direction = _direction;
    id = _id;
}

int Voiture::getPosX() const {
    return posX;
}
    
int Voiture::getPosY() const {
    return posY;
}
    

int Voiture::getTaille() const{
    return taille;
}

int Voiture::getDirection() const{\
    return direction;
}

int Voiture::getId() const{
    return id;
}