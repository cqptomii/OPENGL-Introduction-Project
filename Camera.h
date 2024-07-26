#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glad/glad.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
enum CAM_INPUT {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGTH
};
class Camera
{
private:
	
	glm::vec3 position;
	glm::vec3 direction;

	glm::vec3 Wvup = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 rightAxis;
	glm::vec3 upAxis;

	float FOV;
	float MovementSpeed;
	float MouseSensivity;
	float EulerYaw;
	float EulerPitch;

	float MaxSpeed = 10.0f;
public:
	Camera();
	Camera(glm::vec3 position, glm::vec3 direction, float fov, float speed);

	void reloadCamParameter();
	void handleCamInput(CAM_INPUT INPUT,float deltaTime);

	glm::vec4 getViewMatrix();

	// Getters and Setters
	glm::vec3 getPosition();
	void setPosition(glm::vec3 pos);
	glm::vec3 getDirection();
	void setDirection(glm::vec3 direction);
	float getFOV();
	void setFOV(float fov);
	float getMouseSensivity();
	void setMouseSensivity(float sens);
	float getMovementSpeed();
	void setMovementSpeed(float speed);
	float getYaw();
	void setYaw(float angle);
	float getPitch();
	void setPitch(float angle);

};

#endif // !CAMERA_HPP

