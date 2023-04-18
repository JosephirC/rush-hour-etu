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

        /** @brief Constructeur de Car */
        Car();

        /** @brief Constructeur de Car avec des paramètres
            @param _posX : position x de la voiture
            @param _posY : position y de la voiture
            @param _size : taille de la voiture
            @param _direction : direction de la voiture
            @param _id : numéro d'identification de la voiture
        */
        Car(int _posX, int _posY, int _size, int _direction, int _id);

        /** @brief Constructeur par copie de Car
            @param car : voiture à copier
        */
        Car(const Car& car);

        /** @brief Accesseur de la position X de la voiture
            @return int : renvoie la position X de la voiture 
        */
        int getPosX() const;

        /** @brief Accesseur de la position Y de la voiture
            @return int : renvoie la position Y de la voiture 
        */
        int getPosY() const;
        
        /** @brief Accesseur de la taille de la voiture
            @return int : renvoie la taille de la voiture 
        */
        int getCarSize() const;
        
        /** @brief Accesseur de la direction de la voiture
            @return int : renvoie la direction de la voiture 
        */
        int getDirection() const;
        
        /** @brief Accesseur du numéro d'identification de la voiture
            @return int : renvoie le numéro d'identification de la voiture 
        */
        int getId() const;

        /** @brief Mutateur de la position X de la voiture
            @param x : nouvelle position X de la voiture
        */
        void setPosX(int x);

        /** @brief Mutateur de la position Y de la voiture
            @param y : nouvelle position Y de la voiture
        */
        void setPosY(int y);

        /** @brief Mutateur de la taille de la voiture
            @param s : nouvelle taille de la voiture
        */
        void setSize(int s);
        
        /** @brief Mutateur de la direction de la voiture
            @param d : nouvelle direction de la voiture
        */
        void setDirection(int d);

        /** @brief Mutateur du numéro d'identification de la voiture
            @param i : nouvel id de la voiture
        */
        void setId(int i);

        /** @brief Surcharge de l'opérateur == de la classe Car
            @return bool : si la voiture est la même que celle rentrée en paramètre
        */
        bool operator==(const Car& other) const;
};
#endif