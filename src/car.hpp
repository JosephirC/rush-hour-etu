#ifndef _CAR_HPP
#define _CAR_HPP

class Car {
    private:
        int posX;
        int posY;
        int size;
        int direction; // 1 -> horizontale || 0 -> verticale
        int id;

    public:

        Car();

        Car(int _posX, int _posY, int _size, int _direction, int _id);

        Car(const Car& car); // constructeur par copie

        int getPosX() const;

        int getPosY() const;
        
        int getCarSize() const;
        
        int getDirection() const;
        
        int getId() const;

        int getSize() const;

        void setPosX(int x);

        void setPosY(int y);

        void setSize(int s);
        
        void setDirection(int d);

        void setId(int i);

        bool operator==(const Car& other) const;
};
#endif