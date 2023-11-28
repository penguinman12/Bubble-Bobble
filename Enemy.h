#pragma once
#include "Shape3D.h"
#include "Bubble.h"
#include "Texture.h"


class Enemy :public Shape3D
{
public:
	enum FACE { LEFT, RIGHT };
	enum HORIZONTAL_STATE { STOP, MOVE };

	void initialize();
	Enemy(float x, float y, float z, float s);

	float getSize() const;

	void setFace(FACE f);
	void setHorizontalState(HORIZONTAL_STATE hState);
	
	bool isMoving() const;
	

	virtual void draw() const;

private:

	float size;
	FACE face;
	HORIZONTAL_STATE horizontalState = HORIZONTAL_STATE::STOP;
	Texture enemyR;
	Texture enemyL;
};
