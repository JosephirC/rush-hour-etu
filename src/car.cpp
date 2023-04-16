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
    

int Car::getCarSize() const{
    return size;
}

int Car::getDirection() const{
    return direction;
}

int Car::getId() const{
    return id;
}

int Car::getSize() const {
    return size;
}

void Car::setPosX(int x){
    posX = x;
}

void Car::setPosY(int y){
    posY = y;
}

bool Car::operator==(const Car& other) const {
    return (posX == other.posX && 
            posY == other.posY &&
            size == other.size && 
            direction == other.direction &&
            id == other.id);
}
