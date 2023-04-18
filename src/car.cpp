#include "car.hpp"

Car::Car(){
    posX = 0;
    posY = 0;
    size = 0;
    direction = -1;
    id = -1;
}

Car:: Car(int _posX, int _posY, int _size, int _direction, int _id){
    posX = _posX;
    posY = _posY;
    size = _size;
    direction = _direction;
    id = _id;
}

Car::Car(const Car& car){
    posX = car.posX;
    posY = car.posY;
    size = car.size;
    direction = car.direction;
    id = car.id;
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

void Car::setPosX(int x){
    posX = x;
}

void Car::setPosY(int y){
    posY = y;
}

void Car::setCarSize(int s){
    size = s;
}

void Car::setDirection(int d){
    direction = d;
}

void Car::setId(int i){
    id = i;
}

bool Car::operator==(const Car& other) const {
    return (posX == other.posX && 
            posY == other.posY &&
            size == other.size && 
            direction == other.direction &&
            id == other.id);
}
