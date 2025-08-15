#ifndef CUBE_H
#define CUBE_H

#include "vertices_data.h"
#include "texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"


class Cube{
private:
    Texture2D texture;
public: 

    static unsigned int VAO, VBO;
    static unsigned int scale;

    Cube(Texture2D texture)
    :texture(texture)
    { 
        init();
    }

    void init()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, cubeVerticesTCSize, cubeVerticesTC, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void draw(Shader& shader){
        shader.use();
        texture.Bind();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

};

#endif