#include "box.h"
#include "maze.h"
#include <fstream>
#include <iostream>


#define UINT unsigned int
#define BLACK 0
#define WHITE 255

constexpr UINT W = 800, H = 600,
               numBoxes = 20,
               borderThick = 5, // 10 pixels wide 
               numLines = numBoxes + 1,
               totalBorderThick = numLines * borderThick,
               boxWidth  = (W/numBoxes), // - 2 * borderThick,//(W - totalBorderThick) / numBoxes, 
               boxHeight = (H/numBoxes);// - 2 * borderThick;//(H - totalBorderThick) / numBoxes;

std::string fname = "mazegen.ppm";

int writtenCols = 0;

inline void writeColor(std::ofstream& file, UINT r, UINT g, UINT b){
    file << r << ' ' << g << ' ' << b << '\n';
    writtenCols++;
}

inline void writeColor(std::ofstream& file, UINT c){
    file << c << ' ' << c << ' ' << c << '\n';
    writtenCols++;
}

inline void writeBorder(std::ofstream& file, UINT c){
    for (int i =0; i < borderThick; ++i)
        // for (int j =0; j < borderThick; ++j){
        file << c << ' ' << c << ' ' << c << '\n';
        writtenCols++;
        // }
}

int main(){

    std::cout << "STATS -------- " << '\n' << 
                 "NUM BOXES: " << numBoxes << '\n' <<
                 "Border Thick: " << borderThick << '\n' <<
                 "Num Lines: " << numLines << '\n' << 
                 "Total Border Thickness: " << totalBorderThick << '\n' <<
                 "Box Width: " << boxWidth << '\n' <<
                 "Box Height: " << boxHeight << '\n' << 
                 "--------\n";

    Maze myMaze(numBoxes);

    std::ofstream file {fname};
    file << "P3\n";
    file << W << ' ' << H << "\n255\n";

    for (int i =0 ; i < H; i++){
        for (int j =0; j < W; j++){
            int ind1 = i / boxHeight;
            int ind2 = j / boxWidth;        
            Box box = myMaze.grid[ind1][ind2];
            int color = WHITE;
            if ((ind1==0 && ((i < ind1 * boxHeight + borderThick)) && 
                !box.connectedTo(Box::CN_UP))  || 
                (ind2 == 0 && (j < ind2 * boxWidth + borderThick) && 
                !box.connectedTo(Box::CN_LEFT)) || 
                ((j > (ind2 + 1)*boxWidth - borderThick) && 
                !box.connectedTo(Box::CN_RIGHT)) ||
                (((i > (ind1 + 1)*boxHeight - borderThick)) && 
                !box.connectedTo(Box::CN_DOWN)) )  
                color = BLACK;
            writeColor(file, color);
        }
    }
    std::cout << "Done. Wrote " << writtenCols << " colors" << std::endl;

    for (int k =0; k < numBoxes; ++k){
        std::cout << "ROW \n";
        for (int l =0; l < numBoxes; ++l){
            Box box = myMaze.grid[k][l];
            std::cout << "Box: " << box.connectedTo(Box::CN_LEFT) << ' '
                      << box.connectedTo(Box::CN_RIGHT) << ' ' <<
                      box.connectedTo(Box::CN_UP) << ' ' << box.connectedTo(Box::CN_DOWN) << '\n'; 
        }
    }
}