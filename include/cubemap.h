#ifndef CUBEMAP_H
#define CUBEMAP_H

#include "vertices_data.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"


class Cubemap{
private:
    unsigned int textureId, VAO, VBO;

public:
    Cubemap(unsigned int textureId)
        :textureId(textureId)
        {
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glBufferData(GL_ARRAY_BUFFER, cubeVerticesSize, cubeVertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

    void draw(Shader& shader){
        shader.use();
        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureId);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
};

#endif