#pragma once
#include "Material.h"
#include <iostream>
#include <ctime>
#include <random>

class Shape3D
{
public:
	Shape3D();
	Shape3D(float x, float y, float z);

	void setCenter(const Vector3f& c);
	Vector3f getCenter() const;
	void setVelocity(const Vector3f& v);
	Vector3f getVelocity() const;
	void setAcceleration(const Vector3f& a);
	Vector3f getAcceleration() const;

	void setRandomVelocity();
	void setRandomMaterial();

	void move();

	virtual void draw() const = 0;

protected:
	Vector3f center;
	Vector3f velocity;
	Vector3f acceleration;

	Material mtl;
};

