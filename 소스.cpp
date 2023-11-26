#include <iostream>
#include <vector>
#include <ctime>

#include "Constants.h"
#include "Light.h"

#include "Player.h"
#include "Platform.h"
#include "Texture.h"

#include <GL/freeglut.h>

using namespace std;
int pl = 0;
int stage = 0;


Light light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);

clock_t start_t = clock();
clock_t end_t;
Player player(-boundaryX + PLAYER_SIZE * 1.5f, -boundaryY + PLAYER_SIZE * 1.5f, 0.0f, PLAYER_SIZE);
Platform ground(0.0f, -boundaryY + PLAYER_SIZE * 0.5f, 0.0f, boundaryX * 2, PLAYER_SIZE);
Platform ground2(-boundaryY + PLAYER_SIZE * 0.5f, 0.0f, 0.0f, PLAYER_SIZE, boundaryY * 2);
Platform ground3(0.0f, boundaryY - PLAYER_SIZE * 0.5f, 0.0f, boundaryX * 2, PLAYER_SIZE);
Platform ground4(boundaryY - PLAYER_SIZE * 0.5f, 0.0f, 0.0f, PLAYER_SIZE, boundaryY * 2);
Player player1(-boundaryX/3, -boundaryY + PLAYER_SIZE * 5.0f, 0.0f, PLAYER_SIZE);
Player player2(boundaryX/3, -boundaryY + PLAYER_SIZE * 5.0f, 0.0f, PLAYER_SIZE);

Platform pf1(-boundaryX / 2, -boundaryY / 2, 0.0f, boundaryX, PLAYER_SIZE);
Platform pf2(boundaryX / 2, boundaryY / 4, 0.0f, boundaryX, PLAYER_SIZE);


vector<Bubble> bubbles;
vector<Player> enemy;
Texture texture1;
Texture texture2;

void togglePl(int value) {
	pl = (pl + 1) % 2;
	if (pl) 
		player1.shootBubble();
	else
		player2.shootBubble();
	
	glutPostRedisplay();
	glutTimerFunc(1000, togglePl, 1);
}

void initialize() {
	//player.setVerticalState(Player::VERTICAL_STATE::FALL);
	player.setAcceleration(Vector3f(0.0f, -0.5f, 0.0f));
	texture1.initializeTexture("Front Image1.png");
	texture2.initializeTexture("Front Image2.png");
}

void idle() {
	end_t = clock();

	if ((float)(end_t - start_t) > 1000 / 30.0f) {
		if (player1.isMoving())
			player1.move();

		for (int i = 0; i < bubbles.size(); i++) {
			bubbles[i].move();
			//버블 크기 조절
			if(bubbles[i].getRadius() <= PLAYER_SIZE/2)
				bubbles[i].setRadius(bubbles[i].getRadius() + 0.5f);
			//버블 y축 이동
			if (bubbles[i].getCenter()[0] - bubbles[i].getRadius() >= boundaryX / 2)
				bubbles[i].setVelocity(Vector3f(0.0f, 3.0f, 0.0f));
			if (bubbles[i].getCenter()[0] + bubbles[i].getRadius() <= -boundaryX / 2)
				bubbles[i].setVelocity(Vector3f(0.0f, 3.0f, 0.0f));
		}

		start_t = end_t;
		if ((float)(end_t - start_t) > 2000) {
			
			start_t = end_t;
		}
		glutPostRedisplay();
	}
}

void displayCharacters(void* font, string str, float x, float y, float red, float green, float blue, float fontSize) {
	
	glColor3f(red, green, blue);

	glPushMatrix();
	glScalef(fontSize, fontSize, 1.0);

	glRasterPos2f(x / fontSize, y / fontSize);

	for (int i = 0; i < str.size(); i++) {
		glutBitmapCharacter(font, str[i]);
	}

	glPopMatrix();
}


void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw 2D
	player1.draw();
	player1.setFace(Player::FACE::RIGHT);
	player2.draw();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture1.getTextureID());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-boundaryX / 1.0f,0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-boundaryX / 1.0f, boundaryY -20.0f );
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(boundaryX / 1.0f, boundaryY -20.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(boundaryX / 1.0f, 0.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture2.getTextureID());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-boundaryX / 1.5f, -boundaryY/2.0f -50.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-boundaryX / 1.5f, -boundaryY/2.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(boundaryX / 1.5f, -boundaryY/2.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(boundaryX / 1.5f, -boundaryY/2.0f - 50.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	// Draw 3D
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(light.getID());
	light.draw();

	for (int i = 0; i < bubbles.size(); i++)
		bubbles[i].draw();

	glDisable(light.getID());
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();
}

void keyboardDown(unsigned char key, int x, int y) {
	
	switch (key)
	{
	case ' ':
		glutLeaveMainLoop();
		if (stage ==0)
			stage = 1;
		else {
			player.shootBubble();
		}
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void specialKeyDown(int key, int x, int y) {

	switch (key)
	{
	case GLUT_KEY_RIGHT:
		player.setFace(Player::FACE::RIGHT);
		player.setHorizontalState(Player::HORIZONTAL_STATE::MOVE);
		break;
	case GLUT_KEY_LEFT:
		player.setFace(Player::FACE::LEFT);
		player.setHorizontalState(Player::HORIZONTAL_STATE::MOVE);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void specialKeyUp(int key, int x, int y) {

	switch (key)
	{
	case GLUT_KEY_RIGHT:
		player.setHorizontalState(Player::HORIZONTAL_STATE::STOP);
		break;
	case GLUT_KEY_LEFT:
		player.setHorizontalState(Player::HORIZONTAL_STATE::STOP);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	// init GLUT and create Window
	if (stage == 0) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
		glutInitWindowPosition(WINDOW_X, WINDOW_Y);
		glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		glutCreateWindow("BUBBLE BOBBLE");
		initialize();
		// register callbacks
		glutDisplayFunc(display);
		glutIdleFunc(idle);
		glutKeyboardFunc(keyboardDown);
		/*
		glutSpecialFunc(specialKeyDown);
		glutSpecialUpFunc(specialKeyUp);
		*/
		glutTimerFunc(1000, togglePl, 1);
		// enter GLUT event processing cycle
		glutMainLoop();
		return 0;
	}
	
}
