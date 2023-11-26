#pragma once

#include "Bubble.h"
#include "Texture.h"
#define _USE_MATH_DEFINES
#include <cmath>

class Player
{
public:
	enum FACE { LEFT, RIGHT };
	enum HORIZONTAL_STATE { STOP, MOVE };
	//enum VERTICAL_STATE { STOP, JUMP, FALL };

	void initialize();
	Player(float x, float y, float z, float s);

	void setCenter(const Vector3f& c);
	Vector3f getCenter() const;
	void setVelocity(const Vector3f& v);
	Vector3f getVelocity() const;
	void setAcceleration(const Vector3f& a);
	Vector3f getAcceleration() const;

	void setFace(FACE f);
	void setHorizontalState(HORIZONTAL_STATE hState);
	//void setVerticalState(VERTICAL_STATE vState);
	Bubble shootBubble();

	bool isMoving() const;
	//bool isJumping() const;
	//bool isFalling() const;

	void move();
	void draw() const;

private:
	Vector3f center;
	Vector3f velocity;
	float size;
	FACE face;
	Vector3f acceleration;
	HORIZONTAL_STATE horizontalState;
	//VERTICAL_STATE verticalState;
};

