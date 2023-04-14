#include <vector>
#include <queue>
#include "solver.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>

Solver::Solver(Grid* grid) {
    uncoveredGrids.push(grid);
}

bool checkContainsGrid(vector<Grid*> grid, string s) {
    for (int i=0; i<grid.size(); i++) {
        string temp = grid[i]->gridToString();
        if (temp == s)
            return true;
    }
    return false;
}

bool checkContainsGrid(std::queue<Grid*> q, string s) {
    while (!q.empty())
    {
        string temp = q.front()->gridToString();
        if (temp == s)    
            return true;
        q.pop();
    }
    return false; 
}

void Solver::solve() {

    int nn = 0;

    bool win = false;

    while (uncoveredGrids.size() > 0 && !win) {

        Grid* grid = uncoveredGrids.front();
        uncoveredGrids.pop();

        string temp = grid->gridToString();
        bool checkEquals = checkContainsGrid(coveredGrids, temp);
        
        if (!checkEquals) { // si cette grille voisine n'est pas dans les grilles covered, on la rajoute dans coveredGrids
            coveredGrids.push_back(grid);

            //-----POUR SAVE LES IMAGES (DEBUG)-----
            // std::string path = "./images_svg/COVERED";
            // path.append(std::to_string(nn));
            // path.append(".svg");
            // ofstream file(path);
            // file << grid->svgHeader() << grid->svgRectangle() << grid->svgFooter(); 
            
            // temporaire pour detecter une win, il faut faire une fonction qui marche pour n'importe quel axe X/Y
            vector<Car> cars = grid->getCarArray();
            for (int h=0; h <cars.size(); h++) {
                if (cars[h].getId() == 0 && cars[h].getPosY()+cars[h].getSize()-1 == grid->getExitY()) {
                    std::cout << "!!!WIN!!!" << std::endl;
                    win = true;
                    int k = 1;

                    while (grid->getParent() != nullptr) { // pour afficher en svg les étapes de résolutions

                        std::string path = "./images_svg/path";
                        path.append(std::to_string(k));
                        path.append(".svg");
                        ofstream file(path);
                        file << grid->svgHeader() << grid->svgRectangle() << grid->svgFooter(); 

                        grid = grid->getParent();
                        k++;
                    }

                    // on rajoute le cas initial
                    std::string path = "./images_svg/path";
                    path.append(std::to_string(k));
                    path.append(".svg");
                    ofstream file(path);
                    file << grid->svgHeader() << grid->svgRectangle() << grid->svgFooter(); 



                }
            }

            vector<Grid*> gridNeighbours = grid->getGridNeighbours();

            for (int j=0; j<gridNeighbours.size(); j++) {
                    string temp2 = gridNeighbours[j]->gridToString();
                    bool checkEquals2 = checkContainsGrid(coveredGrids, temp2);
                    bool checkEquals3 = checkContainsGrid(uncoveredGrids, temp2);

                    if (!checkEquals2 && !checkEquals3) {
                        uncoveredGrids.push(gridNeighbours[j]);
                    } 
            }
        }

        std::cout << "Number of grids covered : " << coveredGrids.size() << std::endl;
        std::cout << "Number of grids left to cover : " << uncoveredGrids.size() << std::endl;
        nn++;
    }
    
}

