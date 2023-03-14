#include "plateau.hpp"
#include "voiture.hpp"
#include <fstream>
#include <sstream>
#include <exception>

Plateau::Plateau(int _largeur, int _longueur) :
largeur(6),
longueur(6)
{
    largeur = _largeur;
    longueur = _longueur;
}

void Plateau::initPlateauVide(){
    
    for(int i = 0; i < largeur; i++){
        for(int j = 0; j < longueur; j++){
            cout << ".";
        } cout << endl;
    }
    cout << endl;
}

void Plateau::ajouterVoiture(const Voiture& v){
    tabVoiture.push_back(v);
}

int Plateau::getSortieX() const{
    return sortiePosX;
}

int Plateau::getSortieY() const{
    return sortiePosY;
}

void Plateau::affichageTabVoiture(){
    for(int i = 0; i < tabVoiture.size(); i++){
        cout << "Voiture --> Id = " << tabVoiture[i].getId() << " X = " << tabVoiture[i].getPosX() << " Y = " << tabVoiture[i].getPosY() 
        << " Taille = " << tabVoiture[i].getTaille() << " Direction " << tabVoiture[i].getDirection() << endl; 
    }
}

void Plateau::ChargerDonnees(const string& filename){
    
    //Lire la premiere ligne (stocker les coordonnees pour sortir la voiture)
    ifstream file(filename.c_str());

    if (file.good())
    {
        int sortieX, sortieY;
        string premiereLine;
        //getline(file, premiereLine);
        
        if(file >> sortieX >> sortieY){
            sortiePosX = sortieX;
            sortiePosY = sortieY;
        }
        else{
            throw length_error("Impossible de lire la sortie du plateau");
        }
        
        int pX, pY; //position X et Y
        int t; //taille du vehicule
        int dir; //direction du vehicule
        int id = 0;

        while(file >> pX >> pY >> t >> dir){
            
            Voiture v(pX, pY, t, dir, id);
            tabVoiture.push_back(v);
            id++;
        }
    }
    else
        throw invalid_argument("Failed to open file...");
    
}

// string Plateau::HeaderSVG() const{
//     stringstream ss;
//     ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 \" width=\"" 
//         << largeur * TAILLE_CASE << "\" height=\"" << longueur * TAILLE_CASE << "\" stroke=\"black\" stroke-width=\"1\" fill=\"none\" >" << endl
//         << "<rect x=\"0""\" y=\"0""\" width=\"600""\" height=\"600""\" stroke=\"black""\" stroke-width=\"15""\" fill=\"none""\" />" << endl;
//     return ss.str();
// }

// string Plateau::RectangleSVG() const{
//     stringstream ss;
//     for (int i = 0; i < tabVoiture.size(); i++) {
//         if(tabVoiture[i].getDirection() == 0){
//              ss << "<rect x=\"" << (tabVoiture[i].getPosY() * TAILLE_CASE) + MARGE << "\" y=\"" << (tabVoiture[i].getPosX() * TAILLE_CASE) + MARGE
//             << "\" width=\"" << TAILLE_CASE - (MARGE * 2) << "\" height=\""
//             << (tabVoiture[i].getTaille() * TAILLE_CASE) - (MARGE * 2) << "\" fill=\"red\" />" << endl;
//         }
//         else{
//             ss << "<rect x=\"" << (tabVoiture[i].getPosY() * TAILLE_CASE) + MARGE << "\" y=\"" << (tabVoiture[i].getPosX() * TAILLE_CASE) + MARGE
//             << "\" width=\"" << (tabVoiture[i].getTaille() * TAILLE_CASE) - (MARGE * 2) << "\" height=\""
//             << TAILLE_CASE - (MARGE * 2) << "\" fill=\"red\" />" << endl;
//         }
//     }
//     return ss.str();
// }

// string Plateau::FooterSVG() const{
//     stringstream ss;
//     ss << "</svg>";
//     return ss.str();
// }

const int STROKE_WIDTH = 1;
const string STROKE_COLOR = "black";
const string FILL_COLOR = "red";

string Plateau::HeaderSVG() const {
    stringstream ss;
    ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 " 
       << largeur * TAILLE_CASE << " " << longueur * TAILLE_CASE 
       << "\" width=\"" << largeur * TAILLE_CASE << "\" height=\"" 
       << longueur * TAILLE_CASE << "\" stroke=\"" << STROKE_COLOR 
       << "\" stroke-width=\"" << STROKE_WIDTH << "\" fill=\"none\">" << endl;
    ss << "<rect x=\"0\" y=\"0\" width=\"" << largeur * TAILLE_CASE 
       << "\" height=\"" << longueur * TAILLE_CASE << "\" stroke=\"" 
       << STROKE_COLOR << "\" stroke-width=\"" << 15 * STROKE_WIDTH 
       << "\" fill=\"none\" />" << endl;
    return ss.str();
}

string Plateau::RectangleSVG() const {
    stringstream ss;
    for (const auto& car : tabVoiture) {
        const int x = car.getPosY() * TAILLE_CASE + MARGE;
        const int y = car.getPosX() * TAILLE_CASE + MARGE;
        const int width = (car.getDirection() == 0) ? TAILLE_CASE - 2 * MARGE : 
                                                       car.getTaille() * TAILLE_CASE - 2 * MARGE;
        const int height = (car.getDirection() == 0) ? car.getTaille() * TAILLE_CASE - 2 * MARGE : 
                                                        TAILLE_CASE - 2 * MARGE;
        ss << "<rect x=\"" << x << "\" y=\"" << y 
           << "\" width=\"" << width << "\" height=\"" << height 
           << "\" fill=\"" << FILL_COLOR << "\" />" << endl;
    }
    return ss.str();
}

string Plateau::FooterSVG() const {
    return "</svg>";
}