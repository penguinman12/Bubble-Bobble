#pragma once
#include "Shape3D.h"
#include "Bubble.h"
#include "Texture.h"
#define _USE_MATH_DEFINES
#include <cmath>

class Player:public Shape3D
{
public:
	enum FACE { LEFT, RIGHT };
	enum HORIZONTAL_STATE { STOP, MOVE };
	enum VERTICAL_STATE { STOPJ, JUMP, FALL };

	void initialize();
	Player(float x, float y, float z, float s);

	float getSize() const;

	void setFace(FACE f);
	void setHorizontalState(HORIZONTAL_STATE hState);
	void setVerticalState(VERTICAL_STATE vState);
	Bubble shootBubble();

	bool isMoving() const;
	bool isJumping() const;
	bool isFalling() const;
	bool isStop() const;

	void draw() const;

private:
	
	float size;
	FACE face;
	HORIZONTAL_STATE horizontalState=HORIZONTAL_STATE::STOP;
	Texture playerR;
	Texture playerL;

	VERTICAL_STATE verticalState;
};
