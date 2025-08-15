#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>


class Texture2D{
public:
    unsigned int width, height, 
                 internalFormat, 
                 imageFormat, wrapS,
                 wrapT, filterMin, 
                 filterMag, ID;

    Texture2D();
    void Bind() const;
    ~Texture2D();

    void Generate(unsigned int width, unsigned int height, 
                  unsigned char *data, unsigned int nChannels, 
                  bool updateInternalFormat);

    static Texture2D FromFile(std::string filePath);
};

#endif