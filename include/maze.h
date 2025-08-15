
#ifndef MAZE_H
#define MAZE_H
#include "box.h"
#include "plane.h"
#include "shader.h"
#include <ostream>
#include <vector>

using GridMatrix = std::vector<std::vector<Box>>;
using UINT = unsigned int;
using Coord = std::pair<int, int>;

Coord operator-(Coord, Coord);
Coord operator+(Coord, Coord);
std::ostream& operator<<(std::ostream&, Coord);

class Maze{
private:
    UINT W, H;
    void generate();
    // glm::mat4 model;
    Plane *mazePlane;

    void _init();

public:
    float boxWidth, boxHeight;
    GridMatrix grid;
    Maze(unsigned int width, unsigned int height);
    Maze(unsigned int width_height);
    ~Maze();
    void draw(Shader& shdr, glm::mat4 prevModel);
    bool connectedTo(Coord box, Coord direction);

    inline bool isValid(Coord c){
        return (c.first >= 0 && c.first<H &&
                c.second >=0 && c.second<W);
    }
};


#endif