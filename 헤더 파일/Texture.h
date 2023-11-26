#pragma once

#include <iostream>
#include <string>
#include <GL/freeglut.h>
#include <FreeImage.h>
using namespace std;

class Texture
{
public:
	Texture();

	FIBITMAP* createBitMap(string filename);
	void generateTexture();
	void initializeTexture(string filename);
	GLuint getTextureID() const;

	GLuint textureID;
	GLubyte* textureData;
	int imageWidth, imageHeight;
};

