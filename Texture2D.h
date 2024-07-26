#pragma once
#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <glad/glad.h>
#include <iostream>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture2D
{
	unsigned int textureID;

	Texture2D(char TexSource[], int ImageFormat);
	void CreateTexture(char TexSource[], int ImageFormat);
	void setTextureParameter(int target, int pname, int param);
};

#endif // !TEXTURE_HPP

