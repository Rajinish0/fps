#include "resource_manager.h"
#include <unordered_map>
#include "stb_image.h"
#include "texture.h"

std::unordered_map<std::string, Texture2D*> textureMap;
std::unordered_map<std::string, Shader*> shaderMap;

void ResourceManager::loadTexture(std::string name, std::string path){
    Texture2D* t = new Texture2D;
    int w, h, c;
    unsigned char *data = stbi_load(path.c_str(), &w, &h, &c, 0);
    t->Generate(w, h, data, c, true);
    textureMap[name] = t;
    stbi_image_free(data);
}

void ResourceManager::loadShader(std::string name, std::string vpath, std::string fpath, std::string gpath){
    Shader* s = new Shader(vpath, fpath, gpath);
    s->use();
    s->setMatrix("proj", glm::mat4(1.0f));
    s->setMatrix("view", glm::mat4(1.0f));
    s->setMatrix("model", glm::mat4(1.0f));
    shaderMap[name] = s;
}

Texture2D* ResourceManager::getTexure(std::string name){
    return textureMap[name];
}

Shader* ResourceManager::getShader(std::string name){
    return shaderMap[name];
}

void ResourceManager::applyToShaders(const std::function<void(Shader*)>& func){
    for (auto& item : shaderMap)
        func(item.second);
}

void ResourceManager::clear(){
    for (auto& item : textureMap)
        glDeleteTextures(1, &item.second->ID);

    for (auto& item : shaderMap)
        glDeleteShader(item.second->shaderProg);
    
    textureMap.clear();
    shaderMap.clear();
}