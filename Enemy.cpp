#include "Enemy.h"
#include "Constants.h"

#include <GL/freeglut.h>



void Enemy::initialize() {
	enemyL.initializeTexture("enemyL.png");
	enemyR.initializeTexture("enemyR.png");
}

Enemy::Enemy(float x, float y, float z, float s)
{
	center[0] = x;
	center[1] = y;
	center[2] = z;

	velocity[0] = velocity[1] = velocity[2] = 0.0f;

	size = s;

	face = FACE::LEFT;
	horizontalState = HORIZONTAL_STATE::STOP;
	initialize();
}

void Enemy::setFace(FACE f) {
	face = f;

	switch (face)
	{
	case Enemy::LEFT:
		setVelocity(Vector3f(-2.0f, velocity[1], velocity[2]));
		break;
	case Enemy::RIGHT:
		setVelocity(Vector3f(2.0f, velocity[1], velocity[2]));
		break;
	default:
		break;
	}
}

void Enemy::setHorizontalState(HORIZONTAL_STATE hState) {
	horizontalState = hState;
}

bool Enemy::isMoving() const {
	return horizontalState == HORIZONTAL_STATE::MOVE;
}

float Enemy::getSize() const {
	return size;
}
void Enemy::draw() const {
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(center[0] - size / 2, center[1] - size / 2, 0);
	glVertex3f(center[0] - size / 2, center[1] + size / 2, 0);
	glVertex3f(center[0] + size / 2, center[1] + size / 2, 0);
	glVertex3f(center[0] + size / 2, center[1] - size / 2, 0);
	glEnd();
	glPopMatrix();
	switch (face)
	{
	case Enemy::LEFT:
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, enemyL.getTextureID());
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(getCenter()[0] - PLAYER_SIZE / 2.0f, getCenter()[1] - PLAYER_SIZE / 2.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(getCenter()[0] - PLAYER_SIZE / 2.0f, getCenter()[1] + PLAYER_SIZE / 2.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(getCenter()[0] + PLAYER_SIZE / 2.0f, getCenter()[1] + PLAYER_SIZE / 2.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(getCenter()[0] + PLAYER_SIZE / 2.0f, getCenter()[1] - PLAYER_SIZE / 2.0f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		break;
	case Enemy::RIGHT:
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, enemyR.getTextureID());
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(getCenter()[0] - PLAYER_SIZE / 2.0f, getCenter()[1] - PLAYER_SIZE / 2.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(getCenter()[0] - PLAYER_SIZE / 2.0f, getCenter()[1] + PLAYER_SIZE / 2.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(getCenter()[0] + PLAYER_SIZE / 2.0f, getCenter()[1] + PLAYER_SIZE / 2.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(getCenter()[0] + PLAYER_SIZE / 2.0f, getCenter()[1] - PLAYER_SIZE / 2.0f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		break;
	default:
		break;
	}
	glEnd();

	//glPopMatrix();
}
