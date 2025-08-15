#include "maze.h"
#include <stack>
#include <iostream>
#include <unordered_set>
#include "utils.h"

Maze::Maze(unsigned int width, unsigned int height)
    :W(width), H(height){
        _init();
    }

Maze::Maze(unsigned int width_height)
    :W(width_height), H(width_height){
        _init();
    }

void Maze::_init(){
    srand(time(NULL));
    this->grid = GridMatrix(H, std::vector<Box>(W));
    std::cout << grid.size() << " " << grid[0].size();
    std::cout << "Generating" << std::endl;
    this->generate();
    std::cout << "finished" << std::endl;
}


struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const {
        auto hash1 = std::hash<T1>{}(pair.first);
        auto hash2 = std::hash<T2>{}(pair.second);
        return hash1 ^ (hash2 << 1); // Combine the two hash values
    }
};


void Maze::generate(){
    std::stack<Coord> stack;
    std::unordered_set<Coord, pair_hash> visited;

    stack.emplace(0, 0);

    while (!stack.empty()){
        Coord c = stack.top();
        visited.insert(c);
        UINT i = c.first, j = c.second;
        Box curBox = grid[i][j];
        std::vector<Coord> neighbours = 
                              {Coord(i-1, j),
                               Coord(i+1, j),
                               Coord(i, j+1),
                               Coord(i, j-1)};

        Coord good = Coord(-1, -1);
        float prob = 0.25f;

        std::vector<Coord> goodNeighbours;
        for (Coord neighbour : neighbours){
            if (isValid(neighbour) && visited.count(neighbour) == 0)
                goodNeighbours.push_back(neighbour);
        }

        // for (Coord neighbour : neighbours){
        //     if (isValid(neighbour) && (visited.count(neighbour) == 0) && 
        //         (random_double() <= prob)){
        //             good = neighbour;
        //             break;
        //     } else {
        //         prob += 0.25f;
        //     }
        // }

        if ( goodNeighbours.size() != 0 ){
            Coord good = goodNeighbours[(std::rand() % (goodNeighbours.size()))];
            Coord dir1 = Coord(good.first-c.first,
                               good.second-c.second);
            Coord dir2 = Coord(c.first-good.first,
                               c.second-good.second);
            std::cout << c.first << ' ' << c.second << ' ' << dir1.first << ' ' << dir1.second << '\n';
            grid[c.first][c.second].connectSide(Box::ijtoC(dir1.first, dir1.second));
            grid[good.first][good.second].connectSide(Box::ijtoC(dir2.first, dir2.second));

            // grid[c.first][c.second].disconnectSide(Box::ijtoC(dir1.first, dir1.second));
            // grid[good.first][good.second].disconnectSide(Box::ijtoC(dir2.first, dir2.second));

            stack.push(good);
        } else {
            stack.pop();
        }
    }
}
