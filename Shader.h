#pragma once
#ifndef SHADER_HPP
#define SHADER_HPP
#include <glad/glad.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
	unsigned int ProgramID;
	unsigned int VertexID, FragmentID;
	void createShader(unsigned int Type,const char Source[]);
public:
	int succes;
	char infoLog[512];

	Shader(char VertexPath[], char FragmentPath[]);
	unsigned int getProgramID();
	void use();
	GLint getLoc(const char name[]);
	void setUniformf(std::string name, float value);
	void setUniformi(std::string name, int value);
	void setUniform2f(std::string name, glm::vec2 value);
	void setUniform3f(std::string name, glm::vec3 value);
	void setUniformMat4f(std::string name, glm::mat4 value);

};
#endif // !SHADER_HPP

