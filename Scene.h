#pragma once

#ifndef SCENE_HPP
#define SCENE_HPP
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Camera.h"

enum OBJ_TYPE {
	Cube
};

Camera MainCamera = Camera();

class Scene
{
private:
	int ScreenWidth;
	int ScreenHeigth;
	GLFWwindow* window;
public:
	bool UseDepth = true;

	void CreateScreen(std::string windowName);
	Scene(int width, int heigth, std::string name, bool UseDepth);
	void DrawScene();
	void addObject(OBJ_TYPE type);
	void setFOV(float fov);
	float getFOV();
	void setMouseSensivity(float sens);
	float getMouseSensivity();
	GLFWwindow* getWindow();

};
void window_size_callback(GLFWwindow* window, int width, int heigth);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void process_input(GLFWwindow* window);

#endif // !SCENE_HPP

