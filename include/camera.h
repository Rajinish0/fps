#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "funcs.h"
#include "audio_manager.h"

class Game;

class Camera {
public:
	enum direc {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	glm::vec3 up;
	glm::vec3 direction;
	glm::vec3 position;
	float yaw;   // rotation around y axis
	float pitch; // rotation around x axis
	float sensitivity; // mouse sensitivity
	double lxpos, lypos;
	bool firstMouse = true;
	int curStep = 1;
	double lastPlayed = 0.0;
	double lastShot = 0.0;
	Game& game;


	void handleMovement(GLFWwindow *window, float dt, AudioManager *audioMgr);
	void move(direc dir, float dt);
	void handleMouse(double xPos, double yPos);
	void updateDirection();
	void incPitch(float increment);
	void incYaw(float increment);
	void shootGun(AudioManager*);
	glm::vec3 getRight();
	glm::mat4 getView();
	Camera(Game& game, float sensitivity = 0.1f);

};