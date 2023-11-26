#pragma once

#include "Vector3f.h"

class Platform
{
public:
	Platform(float x, float y, float z, float w, float h);

	void draw() const;

private:
	Vector3f center;

	float width, height;
};

