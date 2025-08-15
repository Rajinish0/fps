#ifndef RES_MGR_H
#define RES_MGR_H

#include <string>
#include "shader.h"
#include "texture.h"
#include <functional>

class ResourceManager{
private:
    ResourceManager();

public:
    static void loadTexture(std::string name, std::string path);
    static void loadShader(std::string name, std::string vpath, std::string fpath, std::string gpath = "");
    static Texture2D* getTexure(std::string name);
    static Shader* getShader(std::string name);
    static void applyToShaders(const std::function<void(Shader*)>& func);

    static void clear();
};

#endif