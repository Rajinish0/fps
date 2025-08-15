#include "Camera.h"
#include "game.h"

Camera::Camera(Game& game, float sensitivity)
	   :up(glm::vec3(0.0f, 1.0f, 0.0f)), game(game),
		position(glm::vec3(0.0f, 0.0f, 0.0f)),
		pitch(0.0f),
		yaw(-90.0f),
		sensitivity(sensitivity)
	{
	updateDirection();
}

glm::vec3 Camera::getRight() {
	
	glm::vec3 s = glm::cross(direction, up);
	return s;
}

void Camera::updateDirection() {
	direction = 
	glm::normalize(glm::vec3(
		glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch)),
		glm::sin(glm::radians(pitch)),
		glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch))
	));
}


glm::mat4 Camera::getView() {

	glm::mat4 trans(1.0f);

	glm::vec3 right = getRight();
	glm::vec3 camup = glm::cross(right, direction); //bcz direction is flipped
	glm::mat4 rotat = glm::mat4(
		glm::vec4(right, 0.0f),
		glm::vec4(camup, 0.0f),
		glm::vec4(-direction, 0.0f), // so that it doesn't flip the axes of the objs
		glm::vec4(glm::vec3(0.0f), 1.0f)
	);

	rotat = glm::transpose(rotat); // inv(A) = A^T if a is orthonormal

	trans = glm::translate(trans, -position);
	//view = glm::rotate(view, -yaw, glm::vec3(0.0f, 1.0f, 0.0f));
	//view = glm::rotate(view, -pitch, glm::vec3(1.0f, 0.0f, 0.0f));
	return rotat*trans;
}
void Camera::handleMovement(GLFWwindow* window, float dt, AudioManager* audioMgr) {
	glm::vec3 oldPos = position;
	bool moved = false;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		position += direction * glm::vec3(1.0f, 0.0f, 1.0f) * dt;
		// moved = true;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		position -= direction * glm::vec3(1.0f, 0.0f, 1.0f) * dt;
		// moved = true;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		position += getRight() * glm::vec3(1.0f, 0.0f, 1.0f) * dt;
		// moved = true;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		position -= getRight() * glm::vec3(1.0f, 0.0f, 1.0f) * dt;
		// moved = true;
	}

	if ((position != oldPos) && (glfwGetTime() - lastPlayed > 0.3)){
		audioMgr->play2D("audio/pl_step" + std::to_string(curStep) + ".wav");
		curStep = (curStep + 1) % 4 + 1;
		lastPlayed = glfwGetTime();
	}
	

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
		incYaw(dt * sensitivity * 200); updateDirection();
		// yaw += dt * sensitivity * 100; updateDirection();
	} else if ((glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)){
		incYaw(-dt * sensitivity * 200); updateDirection();
		// yaw -= dt * sensitivity * 100; updateDirection();
	} else if ((glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)){
		incPitch(dt * sensitivity * 200); updateDirection();
		// pitch += dt * sensitivity * 100; updateDirection();
	} else if ((glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)){
		incPitch(-dt * sensitivity * 200); updateDirection();
		// pitch -= dt * sensitivity * 100; updateDirection();
	} 
	
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS || 
		glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
		shootGun(audioMgr);
	}
}


void Camera::shootGun(AudioManager *audioMgr){
	double cT = glfwGetTime();
	if (cT - lastShot > 0.2){
		audioMgr->play2D("audio/shot.wav");
		lastShot = cT;
		incPitch(1.0f); updateDirection();
		this->game.handleShot();
	} 
}

void Camera::move(direc d, float dt) {
	switch (d) {
		case UP:
			position += direction * dt;
			break;
		case DOWN:
			position -= direction * dt;
			break;
		case RIGHT:
			position += getRight() * dt;
			break;
		case LEFT:
			position -= getRight() * dt;
			break;
	}
}

void Camera::incPitch(float increment) {
	this->pitch += increment;
	this->pitch = funcs::clamp(this->pitch, -45.0f, 45.0f);
}

void Camera::incYaw(float increment) {
	this->yaw += increment;
	this->yaw = (this->yaw > 360.0f || this->yaw < -360.0f) ? 0 : this->yaw;
	// this->yaw = funcs::clamp(this->yaw, -360.0f, 360.0f);
}

void Camera::handleMouse(double xPos, double yPos) {
	if (firstMouse) {
		lxpos = xPos;
		lypos = yPos;
		firstMouse = false;
		return;
	}

	float dx = xPos - lxpos;
	float dy = lypos - yPos;

	incYaw(dx * sensitivity);
	incPitch(dy * sensitivity);

	// yaw += dx * sensitivity;
	// pitch += dy * sensitivity;

	// if (pitch > 89.0f)
	// 	pitch = 89.0f;
	// else if (pitch < -89.0f)
	// 	pitch = -89.0f;
	// yaw = (yaw > 360) ? (yaw - 360) : (yaw < -360) ? yaw + 360 : yaw;

	updateDirection();

	lxpos = xPos;
	lypos = yPos;
}
