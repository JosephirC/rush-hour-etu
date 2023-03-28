#ifndef _Car_HPP
#define _Car_HPP

class Car {
    private:
        int posX;
        int posY;
        int size;
        int direction; // 1 -> horizontale || 0 -> verticale
        int id;

    public:

        Car(int _posX, int _posY, int _size, int _direction, int _id);

        int getPosX() const;

        int getPosY() const;
        
        int getCarSize() const;
        
        int getDirection() const;
        
        int getId() const;

        void setPosX(int x);

        void setPosY(int y);
};
#endif