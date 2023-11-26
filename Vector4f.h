#pragma once
class Vector4f
{
public:
	Vector4f();
	Vector4f(float x, float y, float z, float w);
	void setPos(float x, float y, float z, float w);

	float& operator[](const int i);
	float operator[](const int i) const;

private:
	float pos[4];
};

