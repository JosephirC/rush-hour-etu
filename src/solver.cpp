#include <vector>
#include <queue>
#include "solver.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

Solver::Solver(Grid* grid) {
    uncoveredGrids.push(grid);
}

//fonction solve youssef
void Solver::solve1() {
    while (uncoveredGrids.size() > 0) {
        //verifier que chaque gridNeighbor n'a pas deja ete cover/parcouru
	    //ajouter a coveredGrid

        /**********DEBUUG******/

        cout << endl;
        cout << "Je traite les uncovered grid" << endl; 
        cout << "INIT : uncoveredGrids size : " << uncoveredGrids.size() << endl;

        cout << endl;

        cout << "Je traite les covered grid" << endl;
        cout <<"INIT : coveredgrids size : " << coveredGrids.size() << endl; 
        cout << endl;


        /************************/
        Grid* grid = uncoveredGrids.front();
        uncoveredGrids.pop();
        vector<Grid*> gridNeighbours = grid->getGridNeighbours();


        /********DEBUG*********/
        // for(int i =0; i < gridNeighbours.size(); i++){
        //     gridNeighbours[i]->displayGridId();
        // }
        cout << endl << "Origianl Neighbours Size " << gridNeighbours.size() << endl;
        cout << endl << "NEW? Neighbours Size " << grid->getGridNeighbours().size() << endl;




        /************END DEBUG***************/


        if(std::find(coveredGrids.begin(), coveredGrids.end(), grid) != coveredGrids.end()){
            std::cout << "Grid is already in coveredGrids " << std::endl;
        }
        else {
            coveredGrids.push_back(grid);
            
            /***************DEBUG************/
            cout << "TEST : BEFORE PUSHING NEIGHBOUR GRIDS IN UNCOVERED GRIDS : size = " << uncoveredGrids.size() << endl << endl; 
            



            for(int i=0; i<gridNeighbours.size(); i++){
                if(std::find(coveredGrids.begin(), coveredGrids.end(), gridNeighbours[i]) != coveredGrids.end()){
                    std::cout << "Grid " << i << " is in uncoveredGrids " << std::endl;
                    gridNeighbours[i]->displayGridId();
                    uncoveredGrids.push(gridNeighbours[i]);
                }        
            }

            /***************DEBUG************/
            cout << "TEST : AFTER PUSHING NEIGHBOUR GRIDS IN UNCOVERED GRIDS : size = " << uncoveredGrids.size() << endl << endl; 

        }        
    }
}

//fonction solveur edgar
void Solver::solve() {
    while (uncoveredGrids.size() > 0) {
        //verifier que chaque gridNeighbor n'a pas deja ete cover/parcouru
	    //ajouter a coveredGrid

        //int j = 0;

        //while (uncoveredGrids.size() > 0 && j< 1000) {
        for (int j=0; j<50; j++) {

            std:cout << coveredGrids.size() << std::endl;

            Grid* grid = uncoveredGrids.front();
            uncoveredGrids.pop();

            // vector<Car> cars = grid->getCarArray();
            // for (const auto& car : cars) {
            //     if (car.getId() == 0 && car.getPosY() == 2) {
            //         std::cout << "éjnkjnkjnkjn" << std::endl;
            //         std::string path = "./images_svg/test.svg";
            //         ofstream file(path);
            //         file << grid->svgHeader() << grid->svgRectangle() << grid->svgFooter(); 

            //     }
            // }

            vector<Grid*> gridNeighbours = grid->getGridNeighbours();
            for (int i =0; i<gridNeighbours.size(); i++) {
                if(!(std::find(coveredGrids.begin(), coveredGrids.end(), gridNeighbours[i]) != coveredGrids.end())) {
                    uncoveredGrids.push(gridNeighbours[i]);
                }

                if(std::find(gridNeighbours.begin(), gridNeighbours.end(), grid) != gridNeighbours.end()){
                    std::cout << "The grid has not been covered " << std::endl;
                    // std::string path = "./images_svg/UNCOVERED";
                    // path.append(std::to_string(j));
                    // path.append(" - ");
                    // path.append(std::to_string(0));
                    // path.append(".svg");
                    // ofstream file(path);
                    // file << gridNeighbours[1]->svgHeader() << gridNeighbours[1]->svgRectangle() << gridNeighbours[1]->svgFooter();
                }


                if(!(std::find(coveredGrids.begin(), coveredGrids.end(), grid) != coveredGrids.end())) { // si cette grille voisine n'est pas dans les grilles covered, on la rajoute dans uncoveredGrids
                    coveredGrids.push_back(grid);

                    std::string path = "./images_svg/COVERED";
                    path.append(std::to_string(j));
                    path.append(".svg");
                    ofstream file(path);
                    file << grid->svgHeader() << grid->svgRectangle() << grid->svgFooter(); 
                }
                else {
                    // std::string path = "./images_svg/DOUBLON";
                    // path.append(std::to_string(j));
                    // path.append(".svg");
                    // ofstream file(path);
                    // file << grid->svgHeader() << grid->svgRectangle() << grid->svgFooter(); 
                }

                //j++;
            }
        }
    }
}

//fonction ne marche pas ? a revoir comment generer plusieurs svg avec des index diff
void Solver::solvedGridsSVG() {
    int i = 1;
    for (auto& grid : coveredGrids) {
        std::string path = "./images_svg/grid_" + std::to_string(i) + ".svg";
        ofstream file(path);
        file << grid->svgHeader() << grid->svgRectangle() << grid->svgFooter();
        i++;
    }
}

vector<Grid*> Solver::getCoveredGrids() const{
    return coveredGrids;
}