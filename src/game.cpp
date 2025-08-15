#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "camera.h"

Game::Game(UINT size)
    :sz(size), maze(size)
{
    std::cout << "init called";
    init();
    // view = glm::translate(view, Z_AXIS * (-10.0f));
    preModel = glm::scale(preModel, glm::vec3(scale));
    preModel = glm::rotate(preModel, glm::radians(-90.0f), X_AXIS);
    scaledBW = maze.boxWidth * scale; 
    scaledBH = maze.boxHeight * scale;
    playerWidth = scaledBW * 0.2f;
    playerHeight = scaledBH * 0.2f;
    camera->position.x -= ( scaledBW * (sz / 2.0f) - scaledBW/2.0f);
    camera->position.z -= ( scaledBH * (sz / 2.0f) - scaledBH/2.0f);
    camera->position.y += (1.0f/(float)sz)*scale;
    spherePos = glm::vec3(camera->position.x + scaledBW, 5.0f, camera->position.z);
    // view = glm::rotate(view, glm::radians(45.0f), X_AXIS);
}

void Game::init(){
    std::cout << "HERE NOW " << std::endl;
    ResourceManager::loadTexture("floor", "textures/wall.jpg");
    ResourceManager::loadShader("floor", "shaders/quad_vshader.glsl", "shaders/quad_fshader.glsl");
    ResourceManager::loadShader("skybox", "shaders/skbox_vshader.glsl", "shaders/skbox_fshader.glsl");
    ResourceManager::loadShader("norm", "shaders/norm_v.glsl", "shaders/norm_f.glsl", "shaders/norm_g.glsl");
    ResourceManager::loadShader("gun", "shaders/model_v.glsl", "shaders/model_f.glsl");
    ResourceManager::loadShader("sphere", "shaders/sp_v.glsl", "shaders/sp_f.glsl");

    camera = new Camera(*this);

    // plane = new Plane(*ResourceManager::getTexure("floor"));
    plane = new Plane("floor");

    std::vector<std::string> faces {
        "textures/faces/right.jpg",
        "textures/faces/left.jpg",
        "textures/faces/top.jpg",
        "textures/faces/bottom.jpg",
        "textures/faces/front.jpg",
        "textures/faces/back.jpg"
    };

    audioMgr = new AudioManager();

    cubeMapId = funcs::loadCubeMap(faces);
    skybox = new Cubemap(cubeMapId);
    std::cout << "IM HERE" << std::endl;

    ResourceManager::applyToShaders(
        [this](Shader *shdr) { 
            shdr->use();
            shdr->setMatrix("proj", proj);
        }
    );
}

Coord Game::zxToIj(float z, float x){
    return Coord(
        (int)((z + scaledBH * sz / 2.0f + scaledBH) / scaledBH) - 1,
        (int)((x + scaledBW * sz / 2.0f + scaledBW) / scaledBW) - 1
    );
}

void Game::draw(){

    Shader* shdr = ResourceManager::getShader("floor");
    shdr->use();
    shdr->setMatrix("proj", proj);


    // tempView = camera->getView();
    // glm::mat4 tempView = glm::translate(view, glm::vec3(0.0f, -1.0f/(float)sz, 0.0f));
    // tempView = glm::rotate(tempView, glm::radians(-90.0f), X_AXIS);
    // tempView = camera->getView()*tempView;
    shdr->setMatrix("view", camera->getView());
    shdr->setMatrix("model", preModel);
    shdr->setVec3("lightPos", camera->position);//glm::vec3(0.0f, 50.0f, 0.0f) );
    // shdr->setVec3("lightPos", glm::vec3(0.0f, 50.0f, 0.0f));
    shdr->setVec3("cameraPos", camera->position);
    glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), X_AXIS);
    shdr->setVec3("lightDir", camera->direction);//glm::vec3(rot*glm::vec4(camera->direction, 0.0f)));
    // shdr->setVec3("lightDir", camera->direction*glm::vec3(1.0f, 1.0f, 1.0f));
    plane->draw(*shdr);
    maze.draw(*shdr, preModel);


    /*
    DEBUGGING NORMAL VECs WITH GEOMETRY SHADER
    */
    Shader *shdr2 = ResourceManager::getShader("norm");
    shdr2->use();
    shdr2->setMatrix("proj", proj);
    shdr2->setMatrix("view", camera->getView());
    shdr2->setMatrix("model", preModel);
    plane->draw(*shdr2);
    maze.draw(*shdr2, preModel);

    Shader *shdr4 = ResourceManager::getShader("sphere");
    shdr4->use();
    shdr4->setMatrix("proj", proj);
    shdr4->setMatrix("view", camera->getView());
    shdr4->setMatrix("model", glm::translate(glm::mat4(1.0f), spherePos));
    shdr4->setVec3("color", sphereCol);
    sphere.draw(*shdr4);

    Shader *shdr3 = ResourceManager::getShader("gun");
    shdr3->use();
    shdr3->setMatrix("proj", proj);
    shdr3->setMatrix("view", camera->getView());
    shdr3->setVec3("lightPos", camera->position);//glm::vec3(0.0f, 50.0f, 0.0f));
    shdr3->setVec3("camPos", camera->position);

    glm::mat4 gunModel(1.0f);
    /*
    Why am i doing it this way instead of getting rid of 
    the view matrix in the shader altogether? Bcz I want the 
    model matrix to put camera in the world coords so that
    I can handle the lighting better
    */

    gunModel = glm::translate(gunModel, camera->position + camera->up*-0.1f + camera->getRight() * 0.1f );// - camera->direction*glm::vec3(0.1f, -0.1f, -0.25f));
    gunModel = glm::rotate(gunModel, glm::radians(-camera->yaw), Y_AXIS);
    /*
    initially the gun is in the x y plane (when the model is first loaded)
    so i rotate it by camera's pitch first around the z axis,
    there are some quirky effects, like u can see more of the gun
    when it's pointed down, but i think this looks nicer.
    */
    gunModel = glm::rotate(gunModel, glm::radians(camera->pitch), Z_AXIS);
    gunModel = glm::scale(gunModel, glm::vec3(0.1f));
    shdr3->setMatrix("model", gunModel);
    gun.draw(*shdr3);


    Shader* skShdr = ResourceManager::getShader("skybox");
    skShdr->use();
    skShdr->setMatrix("proj", proj);
    skShdr->setMatrix("view", glm::mat4(glm::mat3(camera->getView())));
    skShdr->setMatrix("model", glm::scale(glm::mat4(1.0f), glm::vec3(50.0f)));
    skybox->draw(*skShdr);

    // Coord c = zxToIj(camera->position.z, camera->position.x);
    // int y = (camera->position.z + scaledBH * sz / 2 ) / scaledBH;
    // int x = (camera->position.x + scaledBW * sz / 2) / scaledBW;

    // std::cout << "y: "  << c.first
    //           << " x: " << c.second << std::endl; 
}

bool Game::isValidPos(){
    glm::vec3 pos = camera->position;
    glm::vec3 dh = glm::normalize(camera->direction*glm::vec3(1.0f, 0.0f, 1.0f))*(playerHeight/2.0f);
    glm::vec3 dw = glm::normalize(camera->getRight())*(playerWidth/2.0f);
    glm::vec3 tr = pos + dw + dh;
    glm::vec3 tl = pos + dh - dw;
    glm::vec3 br = pos + dw - dh;
    glm::vec3 bl = pos - dh - dw;

    Coord curBox = zxToIj(pos.z, pos.x);
    Coord trBox = zxToIj(tr.z, tr.x);
    Coord tlBox = zxToIj(tl.z, tl.x);
    Coord brBox = zxToIj(br.z, br.x);
    Coord blBox = zxToIj(bl.z, bl.x);

    // std::cout << scaledBW << std::endl;
    // std::cout << "Cur: " << pos.z << ' ' << pos.x << '\n';
    // std::cout << "TR: " << tr.z << ' ' << tr.x << '\n';
    // std::cout << "CB: " << curBox
    //           << "TR: " << trBox 
    //           << "TL: " << tlBox 
    //           << "BR: " << brBox
    //           << "BL: " << blBox;

    if (!maze.isValid(trBox) || !maze.connectedTo(curBox, trBox - curBox)){
        // std::cout << "PROB IN TR " << trBox;
        return false;
    }
    
    if (!maze.isValid(tlBox) || !maze.connectedTo(curBox, tlBox - curBox)){
        // std::cout << "PROB IN TL " << tlBox;
        return false;
    }

    if (!maze.isValid(brBox) || !maze.connectedTo(curBox, brBox - curBox)){
        // std::cout << "PROB IN BR " << brBox; 
        return false;
    }

    if (!maze.isValid(blBox) || !maze.connectedTo(curBox, blBox - curBox)){
        // std::cout << "PROB IN BL " << brBox; 
        return false;
    }
    
    return true;
}

void Game::update(GLFWwindow* window,  float dt){

    glm::vec3 oldPos = camera->position;
    float oldYaw = camera->yaw;
    float oldPitch = camera->pitch;

    camera->handleMovement(window, dt, audioMgr);
    audioMgr->update();

	// if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	// 	camera->position += camera->direction * glm::vec3(1.0f, 0.0f, 1.0f) * dt;

	// if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	// 	camera->position -= camera->direction * glm::vec3(1.0f, 0.0f, 1.0f) * dt;

	// if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	// 	camera->position += camera->getRight() * glm::vec3(1.0f, 0.0f, 1.0f) * dt;

	// if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	// 	camera->position -= camera->getRight() * glm::vec3(1.0f, 0.0f, 1.0f) * dt;
    


	// if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
	// 	camera->incYaw(dt * camera->sensitivity * 200); camera->updateDirection();
	// 	// yaw += dt * sensitivity * 100; updateDirection();
	// } else if ((glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)){
	// 	camera->incYaw(-dt * camera->sensitivity * 200); camera->updateDirection();
	// 	// yaw -= dt * sensitivity * 100; updateDirection();
	// } else if ((glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)){
	// 	camera->incPitch(dt * camera->sensitivity * 200); camera->updateDirection();
	// 	// pitch += dt * sensitivity * 100; updateDirection();
	// } else if ((glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)){
	// 	camera->incPitch(-dt * camera->sensitivity * 200); camera->updateDirection();
	// 	// pitch -= dt * sensitivity * 100; updateDirection();
	// }

    /*
    So, the player is currently a cuboid and the collision detection is
    pretty easy in this format. The problem is when the player is really close to the wall
    and then turns, the cuboid protrudes into the wall, so this way rotation was allowed
    but from there moving in the direction adjacent to the wall was impossible,
    because I don't allow any movement that causes the player to intersect the wall.


    So now I'm not allowing the rotations which cause the player's cuboid to go beyond the wall. 
    I don't like this so:
    TO DO: 
        change the player to a cylinder, this way rotations around the y axis won't be 
        stuck near the wall. The only thing I need to figure out is how to handle
        collisions for this circle and the walls.

    (it's enough to look at the 2d projections for these collisions)
    */

    if (!isValidPos()){
        camera->position = oldPos;
        camera->yaw = oldYaw;
        camera->pitch = oldPitch;
    }

    // camera->handleMovement(window, dt);
    // camera->position.x 
}

void Game::handleMouse(double xPos, double yPos){
    camera->handleMouse(xPos, yPos);
}

void Game::handleShot(){
    std::cout << "HANDLING SHOT" << std::endl;
    if (funcs::rayCollidesSphere(camera->position + camera->getRight() * 0.1f, camera->direction, spherePos, 1.0f)){
        std::cout << "COLLIDED"  << std::endl;
        if (sphereCol == RED)
            sphereCol = BLUE;
        else
            sphereCol = RED;
        std::cout << sphereCol.x << " " << sphereCol.y << " "
                  << sphereCol.z << std::endl;
    }
}

Game::~Game(){
    delete plane;
    delete skybox;
    delete audioMgr;
    delete camera;
    ResourceManager::clear();
}