#include "Player.h"
#include "Constants.h"

#include <GL/freeglut.h>



void Player::initialize() {
	playerL.initializeTexture("playerL.png");
	playerR.initializeTexture("playerR.png");
}

Player::Player(float x, float y, float z, float s)
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

void Player::setCenter(const Vector3f& c) {
	center = c;
}

Vector3f Player::getCenter() const {
	return center;
}

void Player::setVelocity(const Vector3f& v) {
	velocity = v;
}

Vector3f Player::getVelocity() const {
	return velocity;
}

void Player::setAcceleration(const Vector3f& a) {
	acceleration = a;
}

Vector3f Player::getAcceleration() const {
	return acceleration;
}

void Player::setFace(FACE f) {
	face = f;

	switch (face)
	{
	case Player::LEFT:
		setVelocity(Vector3f(-2.0f, 0.0f, 0.0f));
		break;
	case Player::RIGHT:
		setVelocity(Vector3f(2.0f, 0.0f, 0.0f));
		break;
	default:
		break;
	}
}

void Player::setHorizontalState(HORIZONTAL_STATE hState) {
	horizontalState = hState;
}

//void Player::setVerticalState(VERTICAL_STATE vState) {
//	verticalState = vState;
//}

//bool Player::isJumping() const {
//	return verticalState == VERTICAL_STATE::JUMP;
//}
//
//bool Player::isFalling() const {
//	return verticalState == VERTICAL_STATE::FALL;
//}

Bubble Player::shootBubble() {
	Bubble newBubble(0, 20, 20);

	newBubble.setCenter(center);

	switch (face)
	{
	case Player::LEFT:
		newBubble.setVelocity(Vector3f(-5.0f, 0.0f, 0.0f));
		break;
	case Player::RIGHT:
		newBubble.setVelocity(Vector3f(5.0f, 0.0f, 0.0f));
		break;
	default:
		break;
	}
	

	return newBubble;
}

bool Player::isMoving() const {
	return horizontalState == HORIZONTAL_STATE::MOVE;
}

void Player::move() {
	center = center + velocity;
	velocity = velocity + acceleration;
}

void Player::draw() const {
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
	case Player::LEFT:
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, playerL.getTextureID());
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
		glPopMatrix();
		break;
	case Player::RIGHT:
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, playerR.getTextureID());
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
		glPopMatrix();
		break;
	default:
		break;
	}
	glEnd();

	//glPopMatrix();
}
