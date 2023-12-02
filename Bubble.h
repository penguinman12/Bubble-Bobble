#pragma once
#include <vector>
#include <iostream>
#include "Material.h"
using namespace std;
class Bubble {
public:
	Bubble();
	Bubble(float r, int sl, int st);

	void setRadius(float r);
	float getRadius() const;
	void setSlice(int sl);
	void setStack(int st);

	void setCenter(const Vector3f& c);
	Vector3f getCenter() const;
	void setVelocity(const Vector3f& v);
	Vector3f getVelocity() const;
	void setcollision(int c);
	bool getcollision();
	void setMTL(const Material& m);

	void move();
	void draw() const;
	void RandomMaterial();
	void RandomVelocity();
	

private:
	float radius;
	int slice;
	int stack;
	int collision = 0;
	Vector3f center;
	Vector3f velocity;
	Material mtl;
};
