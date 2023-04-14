// #include "car.hpp"
// #include "grid.hpp"
// //#include "sdl.hpp"
// #include <iostream>
// #include <fstream>
// #include "solver.hpp"

// //#define CONSTRUCTOR_COPY
// #define GRID_DISPLAY
// #define LOAD_SVG
// #define GET_NEIGHBORD_CARS

// int main(int argc, char** argv){

//     Grid grid(6,6);
//     //Voiture v(0, 0, 2, 1, 0);

//     grid.initEmptyGrid();
//     //g.ajouterVoiture(v);
//     grid.loadData("./Sujet/puzzle.txt");


//     #ifdef CONSTRUCTOR_COPY
//     {

//         Grid grid1(grid);

//         grid1.changeCarPosition(&grid1, 2, 3,2 );

//         grid1.displayGridId();
//         grid.displayGridId();

//         if(grid1 == grid){
//             cout <<"nous sommes egale" << endl;
//         }
//         else {
//             cout << "aie" << endl;
//         }
//     }
//     #endif


//     cout << "Je display les pos de sortie X : " << grid.getExitX() << " Y : " << grid.getExitY() << endl; 
//     grid.displayCarArray();
//     std::cout << "grille originale :" << std::endl;
//     grid.displayGridId();

//     //Creation du .svg ---> Il faut faire une fonction pour cela !
//     ofstream file("./images_svg/path0.svg");
//     file << grid.svgHeader() << grid.svgRectangle() << grid.svgFooter(); 



//     Solver solution(&grid);
//     solution.solve();


//     // vector<Grid*> test = grid.getGridNeighbours();

//     // for (int i=0; i<test.size(); i++) {
//     //     std::cout << "grille voisine " << i << std::endl;
//     //     test[i]->displayGridId();
//     // }

//     // vector<Grid*> test2 = test[0]->getGridNeighbours();
//     // test[0]->displayGridId();


    





//     // #ifdef LOAD_SVG
//     // {
//     //     //Creation du .svg ---> Il faut faire une fonction pour cela !
//     //     ofstream file("./images_svg/image.svg");
//     //     file << grid.svgHeader() << grid.svgRectangle() << grid.svgFooter(); 
//     // }
//     // #endif
    
//     // vector<Grid> test = grid.getGridNeighbours();

//     // for (int i=0; i<test.size(); i++) {
//     //     std::cout << "grille " << i << std::endl;
//     //     test[i].displayGridId();
//     // }


//     // #ifdef GET_NEIGHBORD_CARS
//     // {
//     //     //test neighbor function
//     //     int carId = 0;
//     //     vector<int> test;

//     //     for(int i = 0; i < grid.getCarArray().size(); i++){
//     //         cout << "Working on Car id : " << carId << endl;
//     //         test =  grid.getNeighboursCars(carId);
//     //         carId++;
//     //         cout << endl;
//     //     }
//     // }
//     // #endif

    
//     return 0;
// }




#include "car.hpp"
#include "grid.hpp"
#include "solver.hpp"
#include <iostream>
#include <fstream>

//#define CONSTRUCTOR_COPY
//#define GRID_DISPLAY
//#define LOAD_SVG
//#define GET_GRID_NEIGHBORS
#define SOLVER_TEST

int main(int argc, char** argv){

    Grid grid(6,6);
    grid.initEmptyGrid();
    grid.loadData("./Sujet/puzzle.txt"); //pk j'ai 50 fils quand je le mets dans le constructeur *_*

    #ifdef CONSTRUCTOR_COPY
    {
        Grid grid1(grid);
        grid1.changeCarPosition(&grid1, 2, 3,2 );      
        grid1.displayGridId();
        grid.displayGridId();

        if(grid1 == grid){
            cout <<"nous sommes egale" << endl;
        }
        
        else {
            cout << "aie" << endl;
        }

        Grid grid2 = Grid(grid);
        if(grid2 == grid1)
            cout<<"2=0" << endl;

    }
    #endif

    #ifdef GRID_DISPLAY
    {
        cout << "Je display les pos de sortie X : " << grid.getExitX() << " Y : " << grid.getExitY() << endl; 
        grid.displayCarArray();
        std::cout << "grille originale :" << std::endl;
        grid.displayGridId();
    }
    #endif

     #ifdef LOAD_SVG
    {
        //Creation du .svg ---> Il faut faire une fonction pour cela !
        ofstream file("./images_svg/test.svg");
        file << grid.svgHeader() << grid.svgRectangle() << grid.svgFooter(); 
    }
    #endif

    #ifdef GET_GRID_NEIGHBORS
    {
        vector<Grid*> test = grid.getGridNeighbours();
        for (int i=0; i<test.size(); i++) {
            std::cout << "grille voisine " << i << std::endl;
            test[i]->displayGridId();
        }
        cout << "taille du test " << test.size() << endl;
    }
    #endif  

    #ifdef SOLVER_TEST
    {
        cout << endl << "SOLVER_TEST " << endl << endl;
   
        Solver solution(&grid);
        solution.solve();
        //sol.solvedGridsSVG();
    }
    #endif

    return 0;
}