#include "Texture.h"

Texture::Texture() {
	textureID = -1;
	textureData = nullptr;
	imageWidth = imageHeight = 0;
}

FIBITMAP* Texture::createBitMap(string filename) {
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename.c_str(), 0);
	if (format == -1) {	// couldn't find image
		exit(-1);
	}
	else if (format == FIF_UNKNOWN) {	// couldn't determine file format
		// attemp to get from file extension
		format = FreeImage_GetFIFFromFilename(filename.c_str());
		if (!FreeImage_FIFSupportsReading(format)) {
			cout << "Detected image format cannot be read!" << endl;
			exit(-1);
		}
	}

	FIBITMAP* bitmap = FreeImage_Load(format, filename.c_str());
	int bitsPerPixel = FreeImage_GetBPP(bitmap);
	cout << "Source image has " << bitsPerPixel << " bits per pixel." << endl;

	FIBITMAP* bitmap32;
	if (bitsPerPixel == 32) {
		cout << "Skipping conversion." << endl;
		bitmap32 = bitmap;
	}
	else {
		cout << "Converting to 32-bits." << endl;
		bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
	}

	return bitmap32;
}

void Texture::generateTexture() {
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, textureData);
}

void Texture::initializeTexture(string filename) {
	FIBITMAP* bitmap32 = createBitMap(filename);
	imageWidth = FreeImage_GetWidth(bitmap32);
	imageHeight = FreeImage_GetHeight(bitmap32);
	textureData = FreeImage_GetBits(bitmap32);

	generateTexture();
}

GLuint Texture::getTextureID() const {
	return textureID;
}
