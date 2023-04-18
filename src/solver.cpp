#include <vector>
#include <queue>
#include "solver.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <set>
#include <filesystem>

Solver::Solver(Grid* grid) {
    uncoveredGrids.push(grid);
}

bool Solver::checkContainsGrid(vector<Grid*> grid, string s) {
    for (int i=0; i<grid.size(); i++) {
        if (grid[i]->getGridString() == s)
            return true;
    }
    return false;
}

bool Solver::checkContainsGrid(std::queue<Grid*> q, string s) {
    while (!q.empty())
    {
        if (q.front()->getGridString() == s)    
            return true;
        q.pop();
    }
    return false; 
}

int Solver::isWinningGrid(Grid* grid) {
    for(int j = 0; j < grid->getCarArray().size(); j++){
        if(grid->getCarArray()[j].getId() == 0) { // on vérifie si la voiture a atteint la sortie en fonction de sa direction
            if ((grid->getCarArray()[j].getDirection() == 1 && grid->getCarArray()[j].getPosY() + grid->getCarArray()[j].getCarSize()-1 == grid->getExitY())
            || (grid->getCarArray()[j].getDirection() == 0 && grid->getCarArray()[j].getPosX() + grid->getCarArray()[j].getCarSize()-1 == grid->getExitX())) {
            
            int k = 1;

            while (grid->getParent() != nullptr) { // pour afficher en svg les étapes de résolutions
                std::string path = "./images_svg/";
                path.append(std::to_string(k));
                path.append(".svg");
                ofstream file(path);
                file << grid->svgHeader() << grid->svgRectangle() << grid->svgFooter(); 

                grid = grid->getParent();
                k++;
            }

            // on rajoute le cas initial
            std::string path = "./images_svg/";
            path.append(std::to_string(k));
            path.append(".svg");
            ofstream file(path);
            file << grid->svgHeader() << grid->svgRectangle() << grid->svgFooter(); 

            std::cout << "Gagnant en " << k-1 << " coups minimum !" <<  std::endl;
            std::cout << "-> Voir le chemin gagnant dans ../images_svg/" <<  std::endl;
            
            return k;
        }
        }
        
    }
    return -1; // pas de solution trouvée
}

int Solver::solve() {

    // On reset le contenu du dossier images_svg
    std::filesystem::remove_all("./images_svg");
    std::filesystem::create_directory("./images_svg");

    int win = -1;
    bool stop = false;

    while (uncoveredGrids.size() > 0 && win == -1 && !stop) {

        std::cout << "Nombre de grilles vues : " << coveredGrids.size() << std::endl;
        std::cout << "Nombre de grilles a decouvrir : " << uncoveredGrids.size() << std::endl;

        Grid* grid = uncoveredGrids.front();
        uncoveredGrids.pop();

        bool checkEquals = checkContainsGrid(coveredGrids, grid->getGridString()); // on vérifie si cette grille n'a pas déjà été traitée
        
        if (!checkEquals) { // si cette grille voisine n'est pas dans les grilles covered, on la rajoute dans coveredGrids
            coveredGrids.push_back(grid);
            win = isWinningGrid(grid); // on vérifie si la grille est gagnante
        }

        if (win==-1) {
            vector<Grid*> gridNeighbours = grid->getGridNeighbours(); // on génère tout les voisins

            for (int j=0; j<gridNeighbours.size(); j++) {
                bool checkEquals2 = checkContainsGrid(coveredGrids, gridNeighbours[j]->getGridString());
                bool checkEquals3 = checkContainsGrid(uncoveredGrids, gridNeighbours[j]->getGridString());

                if (!checkEquals2 && !checkEquals3) { // si la découverte est nouvelle (ni présente dans les grilles vues, ni dans les grilles à voir)
                    uncoveredGrids.push(gridNeighbours[j]); // on la rajoute à la liste des grilles à voir
                } 
            }

            if (uncoveredGrids.size() > 200) { // si la génération prend un peu trop longtemps, on arrete le solveur
                stop = true;
                return -2; // on utilise -2 pour savoir qu'on a arreté le programme parcequ'il prennait longtemps à se résoudre
            }
        }

    }

    return win;
}
