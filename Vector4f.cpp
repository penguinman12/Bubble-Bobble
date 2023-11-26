#include "Vector4f.h"

Vector4f::Vector4f() {
	pos[0] = pos[1] = pos[2] = pos[3] = 0.0f;
}

Vector4f::Vector4f(float x, float y, float z, float w) {
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	pos[3] = w;
}

void Vector4f::setPos(float x, float y, float z, float w) {
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	pos[3] = w;
}

float& Vector4f::operator[](const int i) {
	return pos[i];
}

float Vector4f::operator[](const int i) const {
	return pos[i];
}