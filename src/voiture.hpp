#ifndef _VOITURE_HPP
#define _VOITURE_HPP

class Voiture {
    private:
        int posX;
        int posY;
        int taille;
        int direction; // 1 -> horizontale || 0 -> verticale
        int id;

    public:

        Voiture(int _posX, int _posY, int _taille, int _direction, int _id);

        int getPosX() const;

        int getPosY() const;
        
        int getTaille() const;
        
        int getDirection() const;
        
        int getId() const;
};
#endif