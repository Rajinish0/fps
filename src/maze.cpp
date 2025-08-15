#include "maze.h"
#include <stack>
#include <iostream>
#include <unordered_set>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils.h"
#include <ostream>
#include "resource_manager.h"


Coord operator-(Coord left, Coord right){
    return Coord(left.first - right.first, 
                 left.second - right.second);
}

Coord operator+(Coord left, Coord right){
    return Coord(left.first + right.first,
                 left.second + right.second);
}

std::ostream& operator<<(std::ostream& ost, Coord c){
    ost << "(" << c.first << ',' << c.second << ")\n";
    return ost;
}

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

    boxWidth = 1.0f/((float)W);
    boxHeight = 1.0f/((float)H);

    ResourceManager::loadTexture("mazewall", "textures/container2.png");
    ResourceManager::loadTexture("mazewall_spec", "textures/container2_specular.png");
    mazePlane = new Plane("mazewall", "mazewall_spec");

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
        /*
        Math question: is this still uniformly distributed?
        */
        // for (Coord neighbour : neighbours){
        //     if (isValid(neighbour) && (visited.count(neighbour) == 0) && 
        //         (random_double() <= prob)){
        //             good = neighbour;
        //             break;
        //     } else {
        //         prob += 0.25f;
        //     }
        // }

        std::vector<Coord> goodNeighbours;
        for (Coord neighbour : neighbours){
            if (isValid(neighbour) && visited.count(neighbour) == 0)
                goodNeighbours.push_back(neighbour);
        }

        // if (good.first != -1){
        if (goodNeighbours.size() != 0){
            good = goodNeighbours[(std::rand() % (goodNeighbours.size()))];
            Coord dir1 = Coord(good.first-c.first,
                               good.second-c.second);
            Coord dir2 = Coord(c.first-good.first,
                               c.second-good.second);
            // std::cout << c.first << ' ' << c.second << ' ' << dir1.first << ' ' << dir1.second << '\n';
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


void drawWall(Box::Conns conn, float spx, float spy, float boxWidth, float boxHeight, 
              int i, int j, Shader& shdr, Plane* mazePlane, glm::mat4 prevModel){

    float x = spx + j * boxWidth;
    float y = spy - i * boxHeight;

    switch (conn){
        case Box::CN_DOWN:
            y -= boxHeight;
        case Box::CN_UP:
            x += boxWidth/2.0f;
            break;
        case Box::CN_RIGHT:
            x += boxWidth;
        case Box::CN_LEFT:
            y -= boxHeight/2.0f;
            break;
    }

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(
        model, glm::vec3(x, y, boxHeight/2.0f)
    );

    if (conn == Box::CN_RIGHT || conn == Box::CN_LEFT)
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(boxWidth, boxHeight, 1));

    shdr.setMatrix("model", prevModel*model);

    mazePlane->draw(shdr);
}

bool Maze::connectedTo(Coord box, Coord direc){
    return grid[box.first][box.second].
           connectedTo(
            Box::ijtoC(direc.first, direc.second)
            );
}


void Maze::draw(Shader& shdr, glm::mat4 prevModel){
    float spx = -boxWidth * (W/2); // spx = start pos x
    float spy = boxHeight * (H/2);

    // std::cout << "spx: " << spx  << " spy: " 
    //           << spy << std::endl;

    glm::mat4 view = glm::mat4(1.0f);
    shdr.use();
    for (int i =0; i < H; i++){
        for (int j =0; j < W; j++){

            if (!grid[i][j].connectedTo(Box::CN_DOWN))
                drawWall(Box::CN_DOWN, spx, spy, boxWidth, boxHeight, i, j, shdr, mazePlane, prevModel);

            if (!grid[i][j].connectedTo(Box::CN_RIGHT))
                drawWall(Box::CN_RIGHT, spx, spy, boxWidth, boxHeight, i, j, shdr, mazePlane, prevModel);

            if (!grid[i][j].connectedTo(Box::CN_UP))
                drawWall(Box::CN_UP, spx, spy, boxWidth, boxHeight, i, j, shdr, mazePlane, prevModel);

            if (!grid[i][j].connectedTo(Box::CN_LEFT))
                drawWall(Box::CN_LEFT, spx, spy, boxWidth, boxHeight, i, j, shdr, mazePlane, prevModel);

            /*
            NOT PLANNING on deleting this commented code, bcz it explains
            what's happening in the drawWall function
            */

            // if (!grid[i][j].connectedTo(Box::CN_DOWN)){

            //     glm::mat4 model = glm::mat4(1.0f);
            //     model = glm::translate(
            //         model, glm::vec3(
            //             spx + boxWidth/2.0f  + j * boxWidth, 
            //             spy - boxHeight - i * boxHeight, 
            //             0
            //         )
            //     );
            //     model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            //     model = glm::scale(model, glm::vec3(boxWidth, boxHeight, 0));

            //     shdr.setMatrix("model", model);

            //     mazePlane->draw(shdr);
            // } 
            // if (!grid[i][j].connectedTo(Box::CN_RIGHT)){
            //     glm::mat4 model = glm::mat4(1.0f);
            //     model = glm::translate(
            //         model, glm::vec3(
            //             spx + boxWidth  + j * boxWidth, 
            //             spy - boxHeight/2.0f - i * boxHeight, 
            //             0
            //         )
            //     );
            //     model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            //     model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            //     model = glm::scale(model, glm::vec3(boxWidth, boxHeight, 0));

            //     shdr.setMatrix("model", model);

            //     mazePlane->draw(shdr);
            // }

            // if (!grid[i][j].connectedTo(Box::CN_LEFT)){
            //     glm::mat4 model = glm::mat4(1.0f);
            //     model = glm::translate(
            //         model, glm::vec3(
            //             spx  + j * boxWidth, 
            //             spy - boxHeight/2.0f - i * boxHeight, 
            //             0
            //         )
            //     );
            //     model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            //     model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            //     model = glm::scale(model, glm::vec3(boxWidth, boxHeight, 0));

            //     shdr.setMatrix("model", model);

            //     mazePlane->draw(shdr);
            // }

            // if (!grid[i][j].connectedTo(Box::CN_UP)){
            //     glm::mat4 model = glm::mat4(1.0f);
            //     model = glm::translate(
            //         model, glm::vec3(
            //             spx + boxWidth/2.0f  + j * boxWidth, 
            //             spy - i * boxHeight, 
            //             0
            //         )
            //     );
            //     model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            //     model = glm::scale(model, glm::vec3(boxWidth, boxHeight, 0));

            //     shdr.setMatrix("model", model);

            //     mazePlane->draw(shdr);
            // }

        }
    }
}

Maze::~Maze(){
    delete mazePlane;
}
