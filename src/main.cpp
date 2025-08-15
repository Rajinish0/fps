#include "game.h"
#include "window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "model.h"

#define BLACK 0.0f, 0.0f, 0.0f, 0.0f

unsigned int SZ = 10;
unsigned int W = 800, H = 600;
/*
 i need reference to game further down
 but cant initialize it just yet because 
 it has shaders and textures and everything
 which go berserk if i call functions related to them
 before initializing glad.

 Maybe, it would be better to turn this into a class 
 but this works for now.
*/
Game *game;
float lastTime;


void processInput(GLFWwindow*);
void mouseCallback(GLFWwindow*, double, double);

int main(){
    Window window(W, H);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    game = new Game(SZ);

    glfwSetCursorPosCallback(window.window, mouseCallback);

    glEnable(GL_DEPTH_TEST);

    // unsigned int VAO, VBO;
    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);

    // glBindVertexArray(VAO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // glBufferData(GL_ARRAY_BUFFER, unitQuadVerticesTCSize, unitQuadVerticesTC, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

    Shader shdr {"shaders/quad_vshader.glsl", "shaders/quad_fshader.glsl"} ;

    while (!window.shouldClose()){
        glClearColor(BLACK);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        processInput(window.window);

        // shdr.use();
        // glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 10);
        game->draw();


        window.update();
    }

    glfwTerminate();
    delete game;
    return 0;

}


void processInput(GLFWwindow* window){
    if (!lastTime){
        lastTime = glfwGetTime();
        return;
    }

    float curTime = glfwGetTime();
    float dt = (curTime - lastTime) * 5;
    lastTime = curTime;
    game->update(window, dt);
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos){
    game->handleMouse(xPos, yPos);
}