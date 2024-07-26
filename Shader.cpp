#include "Shader.h"
void Shader::createShader(unsigned int Type, const char Source[]) {
	if (Type == GL_VERTEX_SHADER) {
		this->VertexID = glCreateShader(Type);
		glShaderSource(this->VertexID, 1, &Source, NULL);
		glCompileShader(this->VertexID);

		glGetShaderiv(this->VertexID, GL_COMPILE_STATUS, &succes);
		if (!succes) {
			glGetShaderInfoLog(this->VertexID, sizeof(infoLog), NULL, infoLog);
			std::cout << "ERROR - VERTEX SHADER :: " << infoLog << std::endl;
		}
	}
	else if (Type == GL_FRAGMENT_SHADER) {
		this->FragmentID = glCreateShader(Type);
		glShaderSource(this->FragmentID, 1, &Source, NULL);
		glCompileShader(this->FragmentID);

		glGetShaderiv(this->FragmentID, GL_COMPILE_STATUS, &succes);
		if (!succes) {
			glGetShaderInfoLog(this->FragmentID, sizeof(infoLog), NULL, infoLog);
			std::cout << "ERROR - FRAGMENT SHADER :: " << infoLog << std::endl;
		}
	}
}
Shader::Shader(char VertexPath[], char FragmentPath[]) {
	std::string VertexCode, FragmentCode;
	std::ifstream VertexFile, FragmentFile;

	VertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	FragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try {
		VertexFile.open(VertexPath);
		FragmentFile.open(FragmentPath);

		std::stringstream VertexStream, FragmentStream;

		VertexStream << VertexFile.rdbuf();
		FragmentStream << FragmentFile.rdbuf();

		VertexFile.close();
		FragmentFile.close();

		VertexCode = VertexStream.str();
		FragmentCode = FragmentStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR - FAILED TO LOAD SHADERS DATA " << std::endl;
	}

	createShader(GL_VERTEX_SHADER, VertexCode.c_str());
	createShader(GL_FRAGMENT_SHADER, FragmentCode.c_str());
	
	unsigned int ID = glCreateProgram();
	glAttachShader(ID, this->VertexID);
	glAttachShader(ID, this->FragmentID);
	glLinkProgram(ID);
	
	glGetProgramiv(ID, GL_LINK_STATUS, &succes);
	if (!succes) {
		glGetProgramInfoLog(ID, sizeof(512), NULL, infoLog);
		std::cout << "ERROR - PROGRAM SHADER " << infoLog << std::endl;
		return;
	}
	glDeleteShader(this->VertexID);
	glDeleteShader(this->FragmentID);

	this->ProgramID = ID;
}
unsigned int Shader::getProgramID() {
	return this->ProgramID;
}
void Shader::use() {
	glUseProgram(this->ProgramID);
}
GLint Shader::getLoc(const char name[]) {
	return glGetUniformLocation(this->ProgramID, name);
}
void Shader::setUniformf(std::string name, float value) {
	glUniform1f(getLoc(name.c_str()), value);
}
void Shader::setUniformi(std::string name, int value) {
	glUniform1i(getLoc(name.c_str()), value);
}
void Shader::setUniform2f(std::string name, glm::vec2 value){
	glUniform2f(getLoc(name.c_str()), value.x, value.y);
}
void Shader::setUniform3f(std::string name, glm::vec3 value){
	glUniform3f(getLoc(name.c_str()), value.x, value.y, value.z);
}
void Shader::setUniformMat4f(std::string name, glm::mat4 value) {
	glad_glUniformMatrix4fv(getLoc(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}