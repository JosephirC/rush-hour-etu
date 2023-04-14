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
        
        for(int i=0; i<coveredGrids.size(); i++){
            if(std::find(coveredGrids.begin(), coveredGrids.end(), coveredGrids[i]) != coveredGrids.end()){
                std::cout << "double " << std::endl;
            }
        }


        Grid* grid = uncoveredGrids.front();
        uncoveredGrids.pop();
        vector<Grid*> gridNeighbours = grid->getGridNeighbours();

        if(std::find(coveredGrids.begin(), coveredGrids.end(), grid) != coveredGrids.end()){
            std::cout << "Grid is in coveredGrids " << std::endl;
        }

        coveredGrids.push_back(grid);

        cout <<"coveredGrids size : " << coveredGrids.size() << " uncoveredGrids size : " << uncoveredGrids.size() << endl;

        for(int i=0; i<gridNeighbours.size(); i++){
            if(std::find(coveredGrids.begin(), coveredGrids.end(), gridNeighbours[i]) != coveredGrids.end()){
                std::cout << "Grid " << i << " is in uncoveredGrids " << std::endl;
                uncoveredGrids.push(gridNeighbours[i]);

                std::string path = "./images_svg/COVERED";
                path.append(std::to_string(i));
                path.append(".svg");
                ofstream file(path);
                file << grid->svgHeader() << grid->svgRectangle() << grid->svgFooter();   
            }        
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