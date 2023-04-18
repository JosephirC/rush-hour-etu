#ifndef _PLATEAU_HPP
#define _PLATEAU_HPP

#include "car.hpp"
#include <iostream>
#include <vector>

using namespace std;


class Grid {
    private:
        const int MARGE = 20;
        const int TAILLE_CASE = 100;
        int width;
        int height;
        int exitPosX, exitPosY; // position de sortie
        vector<Car> carArray; // tableau des voitures de la grille
        int gridCarId[6][6]; // grille avec pour chaque case l'id de la voiture qui l'occupe
        Grid* parent; // pointeur vers la grille parent de cette grille
        vector<Grid*> neighbours; // liste des voisins de cette grille
        string gridString; // cette grille sous forme de chaine de caractères (0015110320123 par exemple)

    public : 

        /** @brief Destructeur de Grid */
        ~Grid();

        /** @brief Constructeur de Grid */
        Grid();

        /** @brief Constructeur par copie de Grid
            @param grid : grille à copier
        */
        Grid(const Grid& grid);

        /** @brief Constructeur de Grid avec des paramètres
            @param _width : largeur de la grille
            @param _height : hauteur de la grille
        */
        Grid(int _width, int _height);
        
        /** @brief Initialise une grille vide (-1 comme valeur pour chaque case)
        */
        void initEmptyGrid();

        /** @brief Transforme la grille sous forme de string, plus facile à manipuler
            @return string : la grille sous forme de string (par exemple : 025120200321466684003)
        */
        string gridToString();

        /** @brief Ajoute une voiture dans le tableau de voiture et le tableau representant la grille
            @param v : voiture à ajouter dans la grille
        */
        void addCar(const Car& v);

        /** @brief Actualise la grille contenant les voitures en fonction du vector de voitures fourni en paramètre
            @param carArray : le vector de voitures
        */
        void updateGridCarId(const vector<Car>& carArray);

        /** @brief Affichage de la grille dans la console
        */
        void displayGridId();

        /** @brief Accesseur de la position de sortie X de la grille
            @return int : renvoie la position de sortie X de la grille
        */
        int getExitX() const;

        /** @brief Accesseur de la position de sortie Y de la grille
            @return int : renvoie la position de sortie Y de la grille
        */
        int getExitY() const;

        /** @brief Accesseur de la largeur de la grille
            @return int : renvoie la largeur de la grille
        */
        int getSizeX() const;

        /** @brief Accesseur de la hauteur de la grille
            @return int : renvoie la hauteur de la grille
        */
        int getSizeY() const;

        /** @brief Copie la grille dans la grille passé en paramètre (on retourne la grille actuelle)
            @param int (&gridId)[6][6] : grille utilisée comme grille retournée
        */
        void getGridCarId(int (&gridId)[6][6]);
        
        /** @brief Accesseur du vecteur de voitures
            @return le vecteur de voitures
        */
        vector<Car> getCarArray() const;

        /** @brief Retourne la grille parent à cette grille
            @return Grid* : un pointeur vers la grille parent
        */
        Grid* getParent() const;

        /** @brief Accesseur de la grille sous forme de string
            @return string : la grille transformée en string
        */
        string getGridString();

        /** @brief Mutateur de la largeur de la grille
            @param w : nouvelle largeur de la grille 
        */
        void setWidth(int w);

        /** @brief Mutateur de la hauteur de la grille
            @param h : nouvelle hauteur de la grille 
        */
        void setHeight(int h);

        /** @brief Mutateur de la position de sortie X de la grille
            @param eX : nouvelle position de sortie X de la grille 
        */
        void setExitPosX(int eX);

        /** @brief Mutateur de la position de sortie Y de la grille
            @param eY : nouvelle position de sortie Y de la grille 
        */
        void setExitPosY(int eY);

        /** @brief Mutateur du vector des voitures
            @param car : vector des voitures 
        */
        void setCarArray(vector<Car> car);

        /** @brief Mutateur du parent de la grille
            @param p : Pointeur vers le parent de la grille
        */
        void setParent(Grid* p);

        /** @brief Mutateur de la grille sous forme de string
            @param s : grille sous forme de string
        */
        void setGridString(string s);

        /** @brief Affichage du vecteur de voitures pour débugguer
        */
        void displayCarArray() const;

        /** @brief Chargement de la grille décrite dans le puzzle.txt fourni par le sujet
         * @param filename : chemin du fichier à charger
        */
        void loadData(const string& filename);
        
        /** @brief Construit l'en-tête de l'image svg
         * @return l'en-tête svg sous forme de string
        */
        string svgHeader() const;

        /** @brief Construit l'image svg
         * @return l'image sous forme de string
        */
        string svgRectangle() const;
        
        /** @brief Construit la fin de l'image svg
         * @return la fin du fichier svg sous forme de string
        */
        string svgFooter() const;

        /** @brief Mutateur de la position d'une voiture
            @param id : id de la voiture qu'on souhaite déplacer
            @param newPosX : nouvelle position X de la voiture qu'on souhaite déplacer
            @param newPosY : nouvelle position Y de la voiture qu'on souhaite déplacer
        */
        void changeCarPosition(int id, int newPosX, int newPosY);

        /** @brief Vérifie si la grille passée en paramètre est dans la liste des voisins 
          * @return true si la grille passée en paramètre est déjà un voisin
        */
        bool isInNeighbours(Grid* grid) const;

        /** @brief Genere tout les voisins de la grille
         * @return un vecteur de pointeur vers des grilles
        */
        vector<Grid*> getGridNeighbours();
};

#endif