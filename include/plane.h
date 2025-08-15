#ifndef PLANE_H
#define PLANE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "texture.h"
#include "vertices_data.h"
#include "resource_manager.h"


class Plane{

private:
    // Texture2D texture;
    std::string diffTexture;
    std::string specTexture;

public: 
    unsigned int VAO, VBO;

    Plane(std::string diffTexture, std::string specTexture = "")
        :diffTexture(diffTexture), specTexture(specTexture)
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // glBufferData(GL_ARRAY_BUFFER, unitQuadVerticesTCSize, unitQuadVerticesTC, GL_STATIC_DRAW);
        // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        // glEnableVertexAttribArray(0);

        // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        // glEnableVertexAttribArray(1);

        glBufferData(GL_ARRAY_BUFFER, unitQuadVerticesTCNCSize, unitQuadVerticesTCNC, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(4 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void draw(Shader& shader){
        shader.use();
        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        Texture2D *td = ResourceManager::getTexure(diffTexture);
        glBindTexture(GL_TEXTURE_2D, td->ID);
        // td->Bind();
        shader.setInt("texture_diffuse1", 0);
        shader.setBool("hasSpec", false);
        if (specTexture != ""){
            shader.setBool("hasSpec", true);
            glActiveTexture(GL_TEXTURE0 + 1);
            td = ResourceManager::getTexure(specTexture);
            glBindTexture(GL_TEXTURE_2D, td->ID);
            // td = ResourceManager::getTexure(specTexture);
            // td->Bind();
            shader.setInt("texture_specular1", 1);
        }
        // texture.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

};

#endif