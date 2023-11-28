#pragma once

#include "Vector3f.h"
#include "Shape3D.h"

class Platform:public Shape3D
{
public:
	Platform(float x, float y, float z, float w, float h);

	float getWidth() const;
	float getHeight() const;


	void draw() const;

private:
	float width, height;
};

