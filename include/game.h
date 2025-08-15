#ifndef GAME_H
#define GAME_H

#include "maze.h"
#include "box.h"
#include "plane.h"
#include "cube.h"
#include "vertices_data.h"
// #include "camera.h"
#include "cubemap.h"
#include "model.h"
#include "audio_manager.h"
#include "mesh.h"
#include "funcs.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define X_AXIS glm::vec3(1.0f, 0.0f, 0.0f)
#define Y_AXIS glm::vec3(0.0f, 1.0f, 0.0f)
#define Z_AXIS glm::vec3(0.0f, 0.0f, 1.0f)

#define RED X_AXIS
#define GREEN Y_AXIS
#define BLUE Z_AXIS

class Camera;

class Game{
private:
    Maze maze;
    Camera *camera;

    AudioManager *audioMgr;
    Model gun{"models/sniper/Sniper_Rifle.obj"};

    UINT sz, cubeMapId;
    Plane *plane;
    Cubemap *skybox;
    Mesh sphere = funcs::genSphere();
    glm::vec3 spherePos;
    glm::vec3 sphereCol = RED;
    
    const float scale = 30.0f;
    float scaledBW, scaledBH;
    float playerHeight, playerWidth;

    void init();

    glm::mat4 proj = glm::perspective(
        glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f
    );

    glm::mat4 preModel{1.0f};

    bool isValidPos();
    Coord zxToIj(float, float);

public:
    Game(UINT size);
    void draw();
    void update(GLFWwindow* window, float dt);
    void handleMouse(double, double);
    void handleShot();
    ~Game();
};


#endif