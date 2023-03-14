#include "car.hpp"

Car:: Car(int _posX, int _posY, int _size, int _direction, int _id){
    posX = _posX;
    posY = _posY;
    size = _size;
    direction = _direction;
    id = _id;
}

int Car::getPosX() const {
    return posX;
}
    
int Car::getPosY() const {
    return posY;
}
    

int Car::getSize() const{
    return size;
}

int Car::getDirection() const{\
    return direction;
}

int Car::getId() const{
    return id;
}