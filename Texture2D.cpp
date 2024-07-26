#include "Texture2D.h"

Texture2D::Texture2D(char TexSource[], int ImageFormat) {
	CreateTexture(TexSource, ImageFormat);
}
void Texture2D::CreateTexture(char TexSource[], int ImageFormat) {
	glGenTextures(1, &this->textureID);

	glBindTexture(GL_TEXTURE_2D, this->textureID);
	setTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	setTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	setTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	setTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int width, heigth, nrChannels;
	unsigned char* data = stbi_load(TexSource, &width, &heigth, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, ImageFormat, width, heigth, 0, ImageFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ERROR :: FAIED TO LOAD DATA" << std::endl;
		stbi_image_free(data);
		return;
	}
	stbi_image_free(data);
}
void Texture2D::setTextureParameter(int target, int pname, int param) {
	glTexParameteri(target, pname, param);
}