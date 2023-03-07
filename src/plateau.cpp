#include "plateau.hpp"
#include "voiture.hpp"
#include <fstream>
#include <sstream>
#include <exception>

Plateau::Plateau(int sX, int sY) :
sizeX(6),
sizeY(6)
{
    sizeX = sX;
    sizeY = sY;
}

void Plateau::initPlateauVide(){
    
    for(int i = 0; i < sizeX; i++){
        for(int j = 0; j < sizeY; j++){
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

string Plateau::HeaderSVG() const{
    stringstream ss;
    ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 \" width=\"" 
        << sizeX << "\" height=\"" << sizeY << "\">" << endl;

    return ss.str();
}

string Plateau::RectangleSVG() const{
    stringstream ss;
    for (int i = 0; i < tabVoiture.size(); i++) {
        ss << "<rect x=\"" << tabVoiture[i].getPosX() << "\" y=\"" << tabVoiture[i].getPosY()
            << "\" width=\"" << tabVoiture[i].getTaille() << "\" height=\""
            << tabVoiture[i].getTaille() << "\" fill=\"red\" />" << endl;
    }
    return ss.str();
}

string Plateau::FooterSVG() const{
    stringstream ss;
    ss << "</svg>" << endl;
    return ss.str();
}


//Utiliser ofstream ou string stream ??? Difference ?
//reponse : utiliser un string stream pour pouvoir forger les differents svg

//void Plateau:: ToSVG(const Voiture& v, const Plateau& p, const char* filename) {
    /* ofstream file(filename);
    if (!file) {
        cerr << "Error: Unable to create file " << filename << endl;
        return;
    }

    file << "<svg width=\"" << p.sizeX << "\" height=\"" << p.sizeY << "\">" << endl;
    file << "<rect width=\"" << p.sizeX << "\" height=\"" << p.sizeY << "\" fill=\"white\"/>" << endl;
    file << "<rect x=\"" << v.getPosX() << "\" y=\"" << v.getPosY() << "\" width=\"" << v.getTaille() << "\" height=\"" << v.getTaille() << "\" fill=\"blue\"/>" << endl;
    file << "</svg>" << endl;

    file.close(); */

    
//}
