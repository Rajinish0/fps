
#ifndef MAZE_H
#define MAZE_H
#include "box.h"
#include <vector>

using GridMatrix = std::vector<std::vector<Box>>;
using UINT = unsigned int;
using Coord = std::pair<int, int>;

class Maze{
private:
    UINT W, H;
    void generate();

    inline bool isValid(Coord c){
        return (c.first >= 0 && c.first<H &&
                c.second >=0 && c.second<W);
    }

    void _init();

public:
    GridMatrix grid;
    Maze(unsigned int width, unsigned int height);
    Maze(unsigned int width_height);
};


#endif