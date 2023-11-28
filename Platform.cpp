#include "Platform.h"

#include <GL/freeglut.h>

Platform::Platform(float x, float y, float z, float w, float h)
{
	center[0] = x;
	center[1] = y;
	center[2] = z;

	width = w;
	height = h;
}

float Platform::getWidth() const {
	return width;
}

float Platform::getHeight() const {
	return height;
}

void Platform::draw() const
{
	glPushMatrix();

	glColor3f(0.5f, 0.5f, 0.5f);

	glBegin(GL_QUADS);
	glVertex2d(center[0] - width / 2.0f, center[1] + height / 2.0f);
	glVertex2d(center[0] + width / 2.0f, center[1] + height / 2.0f);
	glVertex2d(center[0] + width / 2.0f, center[1] - height / 2.0f);
	glVertex2d(center[0] - width / 2.0f, center[1] - height / 2.0f);
	glEnd();

	glPopMatrix();
}