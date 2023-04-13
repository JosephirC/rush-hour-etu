#include <vector>
#include <queue>
#include "solver.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>

Solver::Solver(Grid* grid) {
    uncoveredGrids.push(grid);
}

void Solver::solve1() {
     int j =0;
    while (uncoveredGrids.size() > 0 && j < 60) {
        //verifier que chaque gridNeighbor n'a pas deja ete cover/parcouru
	    //ajouter a coveredGrid


       

        Grid* grid = uncoveredGrids.front();
        uncoveredGrids.pop();
        vector<Grid*> gridNeighbours = grid->getGridNeighbours();

        for(int i=0; i<gridNeighbours.size(); i++){
            uncoveredGrids.push(gridNeighbours[i]);
        }

        if(std::find(gridNeighbours.begin(), gridNeighbours.end(), grid) != gridNeighbours.end()){
            std::cout << "The grid has not been covered " << std::endl;
            coveredGrids.push_back(grid);

            // std::string path = "./images_svg/";
            // path.append(std::to_string(0));
            // path.append(", ");
            // path.append(std::to_string(j));
            // path.append(".svg");
            // ofstream file(path);
            // file << gridNeighbours[j]->svgHeader() << gridNeighbours[j]->svgRectangle() << gridNeighbours[j]->svgFooter(); 
            




        }
        else{
            std:cout << "This grid has been covered" << std::endl;
        }
        
        j++;
       
    }
}

void Solver::solve() {

    //while (uncoveredGrids.size() > 0) {
    //for (int j=0; j<1; j++) {

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
        coveredGrids.push_back(grid);

        for (int i=0; i<gridNeighbours.size(); i++) {
            if(!(std::find(coveredGrids.begin(), coveredGrids.end(), gridNeighbours[i]) != coveredGrids.end())) { // si cette grille voisine n'est pas dans les grilles covered, on la rajoute dans uncoveredGrids
                uncoveredGrids.push(gridNeighbours[i]);
                //coveredGrids.push_back(gridNeighbours[i]);


                std::string path = "./images_svg/";
                path.append(std::to_string(0));
                path.append(", ");
                path.append(std::to_string(i));
                path.append(".svg");
                ofstream file(path);
                file << gridNeighbours[i]->svgHeader() << gridNeighbours[i]->svgRectangle() << gridNeighbours[i]->svgFooter(); 
            }
            else {
                std::cout << "la grille 0, " << i << " est deja dans covered" << std::endl;
            }
        }

        // for (int h=0; h<gridNeighbours.size(); h++) {
        //     std::string path = "./images_svg/";
        //     path.append(std::to_string(0));
        //     path.append(", ");
        //     path.append(std::to_string(h));
        //     path.append(".svg");
        //     ofstream file(path);
        //     file << gridNeighbours[h]->svgHeader() << gridNeighbours[h]->svgRectangle() << gridNeighbours[h]->svgFooter(); 
        // }



        
        Grid* grid2 = uncoveredGrids.front();
        uncoveredGrids.pop();
        vector<Grid*> gridNeighbours2 = grid2->getGridNeighbours();
        coveredGrids.push_back(grid2);

        for (int i=0; i<gridNeighbours2.size(); i++) {
            if(!(std::find(coveredGrids.begin(), coveredGrids.end(), gridNeighbours2[i]) != coveredGrids.end())) { // si cette grille voisine n'est pas dans les grilles covered, on la rajoute dans uncoveredGrids
                uncoveredGrids.push(gridNeighbours2[i]);

                std::string path = "./images_svg/blablabla";
                path.append(std::to_string(0));
                path.append(", ");
                path.append(std::to_string(i));
                path.append(".svg");
                ofstream file(path);
                file << gridNeighbours2[i]->svgHeader() << gridNeighbours2[i]->svgRectangle() << gridNeighbours2[i]->svgFooter(); 
            }
            else {
                std::cout << "la grille 1, " << i << " est deja dans covered" << std::endl;
            }
        }

        // vector<Car> cars = grid->getCarArray();
        // for (const auto& car : cars) {
        //     if (car.getId() == 0 && car.getPosY() == 2) {
        //         std::cout << "éjnkjnkjnkjn" << std::endl;
        //         std::string path = "./images_svg/test.svg";
        //         ofstream file(path);
        //         file << grid->svgHeader() << grid->svgRectangle() << grid->svgFooter(); 

        //     }
        // }

       


    //}
}