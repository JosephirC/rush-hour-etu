#include <vector>
#include <queue>
#include "solver.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <set>

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

                    cout << "grid parent" << grid->getParent() << endl;

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

        // std::cout << "Number of grids covered : " << coveredGrids.size() << std::endl;
        // std::cout << "Number of grids left to cover : " << uncoveredGrids.size() << std::endl;
        nn++;
    }
    
}

vector<Grid*> Solver::getCoveredGrids() const{
    return coveredGrids;
}

//fonction pour commencer la generation des puzzle
void Solver::solveALL() { 

    int nn = 0;

    vector<Grid*> test;

    while (uncoveredGrids.size() > 0) {

        Grid* grid = uncoveredGrids.front();
        uncoveredGrids.pop();

        string temp = grid->gridToString();
        bool checkEquals = checkContainsGrid(coveredGrids, temp);
        
        if (!checkEquals) { // si cette grille voisine n'est pas dans les grilles covered, on la rajoute dans coveredGrids
            coveredGrids.push_back(grid);
            


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

    //test de double
    int doubleCount =0;
    for(int i=0; i<coveredGrids.size(); i++){
        if(std::find(coveredGrids.begin(), coveredGrids.end(), coveredGrids[i]) != coveredGrids.end()){
            //std::cout << "double " << std::endl;
            doubleCount++;
        }
    }

    cout << "double count " << doubleCount << endl;
}

bool Solver::isWinningGrid(Grid* grid){
    for(int j = 0; j < grid->getCarArray().size(); j++){
        if(grid->getCarArray()[j].getId() == 0 && grid->getCarArray()[j].getPosY() + grid->getCarArray()[j].getSize()-1 == grid->getExitY()){
            return true;
        }
    }
    return false;
}

vector<Grid*> Solver::getWinningGrids(){

    std::set<Grid*> uniqueWinningGrids;

    for(int i = 0; i < coveredGrids.size(); i++){
        for(int j = 0; j < coveredGrids[i]->getCarArray().size(); j++){
            if(coveredGrids[i]->getCarArray()[j].getId() == 0 && coveredGrids[i]->getCarArray()[j].getPosY() + coveredGrids[i]->getCarArray()[j].getSize()-1 == coveredGrids[i]->getExitY()
            && !isWinningGrid(coveredGrids[i]->getParent())){
                uniqueWinningGrids.insert(coveredGrids[i]);
            }
        }
    }

    // Convert the set to a vector
    vector<Grid*> winningGrids(uniqueWinningGrids.begin(), uniqueWinningGrids.end());
    return winningGrids;
}

void Solver::solvedGridsSVG(Grid* grid, string filenumber){

    std::string path = "./solved_svg/winningGrid";
    path.append(filenumber);
    path.append("_");

    //for(int i = 0; i < grid.size(); i++){
        //path.append(std::to_string(i));
        path.append(".svg");
        ofstream file(path);
        file << grid->svgHeader() << grid->svgRectangle() << grid->svgFooter(); 
    //}
}


//fonction pour commencer la generation des puzzle
void Solver::solveTest() { 

    int nn = 0;

    vector<Grid*> test;

    while (uncoveredGrids.size() > 0) {

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
            
            vector<Grid*> win = getWinningGrids();

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

        //std::cout << "Number of grids covered : " << coveredGrids.size() << std::endl;
        //std::cout << "Number of grids left to cover : " << uncoveredGrids.size() << std::endl;
        nn++;
    }
}

void Solver::puzzle(){

    vector<Grid*> winningGrids = getWinningGrids();

    cout<<"wining size " << winningGrids.size() << endl;
    coveredGrids[20]->displayGridId();
    winningGrids[337]->displayGridId();


    if(isWinningGrid(winningGrids[337])){
        cout<<"it is" << endl;
    }

}