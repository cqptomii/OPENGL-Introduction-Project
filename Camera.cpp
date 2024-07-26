#include "Camera.h"

Camera::Camera() : position(glm::vec3(0.0f,0.0f,-3.0f)), direction(glm::vec3(0.0f,0.0f,0.0f)), FOV(45.0f), MovementSpeed(2.5f), MouseSensivity(1.0f), EulerYaw(-90.0f), EulerPitch(0.0f) {

}
Camera::Camera(glm::vec3 position, glm::vec3 direction, float fov, float speed){
}
void Camera::reloadCamParameter() {
	this->direction = glm::vec3(1.0f);

	this->direction.x = glm::cos(glm::radians(this->EulerYaw)) * glm::cos(glm::radians(this->EulerPitch));
	this->direction.y = glm::sin(glm::radians(this->EulerPitch));
	this->direction.z = glm::cos(glm::radians(this->EulerPitch)) * glm::sin(glm::radians(this->EulerYaw));
	
	this->direction = glm::normalize(this->direction);

	this->rightAxis = glm::normalize(glm::cross(this->direction, this->Wvup));
	this->upAxis = glm::normalize(glm::cross(this->rightAxis,this->direction));
}
void Camera::handleCamInput(CAM_INPUT INPUT,float deltaTime) {
	float velocity = getMovementSpeed() * deltaTime;
	if (INPUT == FORWARD) {
		this->position += this->direction * velocity;
	}
	if (INPUT == BACKWARD) {
		this->position -= this->direction * velocity;
	}
	if (INPUT == LEFT) {
		this->position -= this->rightAxis * velocity;
	}
	if (INPUT == RIGTH) {
		this->position += this->rightAxis * velocity;
	}
}

glm::vec4 Camera::getViewMatrix() {
	glm::lookAt(this->position, this->position + this->direction, this->Wvup);
}

glm::vec3 Camera::getPosition() {
	return this->position;
}
void Camera::setPosition(glm::vec3 pos) {
	this->position = pos;
}
glm::vec3 Camera::getDirection() {
	return this->direction;
}
void Camera::setDirection(glm::vec3 direction) {
	if (this->direction != this->position) {
		this->direction = direction;
	}
}

void Camera::setFOV(float fov) {
	if (fov < 55.0f && fov > 1.0f) {
		this->FOV = fov;
	}
	if (fov < 1.0f) {
		this->FOV = 1.0f;
	}
	if (fov > 55.0f) {
		this->FOV = 55.0f;
	}
}
float Camera::getFOV() {
	return this->FOV;
}
void Camera::setMouseSensivity(float sens) {
	if (sens < 1.0f && sens > 0.05f) {
		this->MouseSensivity = sens;
	}
	else {
		if (this->MouseSensivity < 0.00f) {
			this->MouseSensivity = 0.05f;
		}
		if (this->MouseSensivity > 1.0f) {
			this->MouseSensivity = 1.0f;
		}
	}
}
float Camera::getMouseSensivity() {
	return this->MouseSensivity;
}
float Camera::getMovementSpeed() {
	return this->MovementSpeed;
}
void Camera::setMovementSpeed(float speed) {
	if(this->MovementSpeed < 1.0f){
		this->MovementSpeed = 1.0f;
	}
	else {
		if (this->MovementSpeed > MaxSpeed) {
			this->MovementSpeed = MaxSpeed;
		}
		else {
			this->MovementSpeed = speed;
		}
	}
}
float Camera::getYaw() {
	return this->EulerYaw;
}
void Camera::setYaw(float angle) {
	if (angle < 360.0f && angle > -360.0f) {
		this->EulerYaw = angle;
	}
}
float Camera::getPitch() {
	return this->EulerPitch;
}
void Camera::setPitch(float angle) {
	if (angle > -89.0f && angle < 89.0f) {
		this->EulerPitch = 89.0f;
	}
	else {
		if (angle < -89.0f) {
			this->EulerPitch = -89.0f;
		}
		else {
			if (angle > 89.0f) {
				this->EulerPitch = 89.0f;
			}
		}
	}
}