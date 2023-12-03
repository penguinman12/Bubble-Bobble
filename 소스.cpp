#include <iostream>
#include <vector>
#include <ctime>

#include "Constants.h"
#include "Light.h"

#include "Enemy.h"
#include "Player.h"
#include "Platform.h"
#include "Texture.h"

#include <GL/freeglut.h>

using namespace std;
int pl = 0;
int stage = 0;
int life = 3;
int enemycount = 3;
int COUNT = 0;
int bubblecount = 0;
int bubblecounter = 0;
Light light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);

clock_t start_t = clock();
clock_t end_t;
Player player(-boundaryX + PLAYER_SIZE * 1.5f, -boundaryY + PLAYER_SIZE * 1.5f, 0.0f, PLAYER_SIZE);
Platform ground(0.0f, -boundaryY + PLAYER_SIZE * 0.5f, 0.0f, boundaryX * 2, PLAYER_SIZE);
Platform ground2(-boundaryY + PLAYER_SIZE * 0.5f, 0.0f, 0.0f, PLAYER_SIZE, boundaryY * 2);
Platform ground3(0.0f, boundaryY - PLAYER_SIZE * 0.25f, 0.0f, boundaryX * 2, PLAYER_SIZE / 2);
Platform ground4(boundaryY - PLAYER_SIZE * 0.5f, 0.0f, 0.0f, PLAYER_SIZE, boundaryY * 2);
Platform F11(-260, -170, 0, 40, 40);
Platform F12(0, -170, 0, 320, 40);
Platform F13(260, -170, 0, 40, 40);
Platform F21(-260, -40, 0, 40, 40);
Platform F22(0, -40, 0, 320, 40);
Platform F23(260, -40, 0, 40, 40);
Platform F31(-260, 90, 0, 40, 40);
Platform F32(0, 90, 0, 320, 40);
Platform F33(260, 90, 0, 40, 40);
Platform F211(-120, -170, 0, 160, 40);
Platform F212(120, -170, 0, 160, 40);
Platform F221(-215, -40, 0, 130, 40);
Platform F222(0, -40, 0, 160, 40);
Platform F223(215, -40, 0, 130, 40);
Platform F231(-120, 90, 0, 160, 40);
Platform F232(120, 90, 0, 160, 40);
Player player1(-boundaryX / 3, -boundaryY + PLAYER_SIZE * 5.0f, 0.0f, PLAYER_SIZE);
Player player2(boundaryX / 3, -boundaryY + PLAYER_SIZE * 5.0f, 0.0f, PLAYER_SIZE);
Enemy enemy1(0, -130, 0, PLAYER_SIZE);
Enemy enemy2(0, 0, 0, PLAYER_SIZE);
Enemy enemy3(0, 130, 0, PLAYER_SIZE);
Enemy enemy21(-120, -130, 0, PLAYER_SIZE);
Enemy enemy22(120, -130, 0, PLAYER_SIZE);
Enemy enemy23(0, 0, 0, PLAYER_SIZE);
Enemy enemy24(-120, 130, 0, PLAYER_SIZE);
Enemy enemy25(120, 130, 0, PLAYER_SIZE);
Platform pf1(-boundaryX / 2, -boundaryY / 2, 0.0f, boundaryX, PLAYER_SIZE);
Platform pf2(boundaryX / 2, boundaryY / 4, 0.0f, boundaryX, PLAYER_SIZE);


vector<Bubble> bubbles;
vector<Player> enemy;
vector<Bubble> effect;
vector<Bubble> chain;
Texture texture1;
Texture texture2;
Texture playerf1;
Texture playerf2;
Texture heart;
Texture gameover;
Texture gameover1;
Texture ALLCLEAR;


bool CollisionDetector(const Player& player, const Bubble& bubble) {
	float distanceX = bubble.getCenter()[0] - player.getCenter()[0];
	float distanceY = bubble.getCenter()[1] - player.getCenter()[1];
	float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

	float collisionDistance = (player.getSize() / 2.0f) + bubble.getRadius();

	if (distance < collisionDistance) {
		return true;
	}
	else {
		return false;
	}
}
bool CollisionDetector(const Enemy& enemy, const Bubble& bubble) {
	float distanceX = bubble.getCenter()[0] - enemy.getCenter()[0];
	float distanceY = bubble.getCenter()[1] - enemy.getCenter()[1];
	float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

	float collisionDistance = (enemy.getSize() / 2.0f) + bubble.getRadius();

	if (distance < collisionDistance) {
		return true;
	}
	else {
		return false;
	}
}
void eff(int n, vector<Bubble>& effect, Bubble& b) {
	Bubble* p;
	p = new Bubble;
	for (int i = 0; i < n; i++) {
		p->RandomMaterial();
		p->RandomVelocity();
		p->setCenter(b.getCenter());
		effect.push_back(*p);
	}
	delete p;

}
bool BubbleCollision(Bubble& a, Bubble& b) {
	float distanceX = a.getCenter()[0] - b.getCenter()[0];
	float distanceY = a.getCenter()[1] - b.getCenter()[1];
	float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

	float collisionDistance = a.getRadius() + b.getRadius();

	if (distance < collisionDistance) {
		return true;
	}
	else {
		return false;
	}

}

void CollisionHandler(Player& player, vector<Bubble>& bubbles) {
	for (int i = 0; i < bubbles.size(); i++) {
		if (CollisionDetector(player, bubbles[i])) {
			if (bubbles[i].getRadius() == 20) {
				eff(10, effect, bubbles[i]);
				chain.push_back(bubbles[i]);

				if (bubbles[i].enemycollision == 1) {
					bubblecount--;
				}
				bubbles.erase(bubbles.begin() + i);
				for (int k = 0; k < chain.size(); k++) {
					for (int j = 0; j < bubbles.size(); j++) {
						if (BubbleCollision(chain[k], bubbles[j])) {
							eff(10, effect, bubbles[j]);
							if (bubbles[j].enemycollision == 1) {
								bubblecount--;
							}
							chain.push_back(bubbles[j]);
							bubbles.erase(bubbles.begin() + j);
						}
					}
				}

			}
			chain.clear();
		}
	}
}

void CollisionHandler(Enemy& enemy, vector<Bubble>& bubbles) {
	for (int i = 0; i < bubbles.size(); i++) {
		if (CollisionDetector(enemy, bubbles[i])) {
			if (bubbles[i].getRadius() < 20) {
				bubbles[i].setRadius(20);
				bubbles[i].setcollision(1);
				bubblecount += 1;
				bubbles[i].enemycollision = 1;
				enemy.setCenter(Vector3f(-1000, -1000, 0));
				enemycount--;
			}
		}
	}
}



bool isCollisionDetected(const Player& player, const Platform& platform) {
	/* Implement: collision detection between player and platform */
	if (((player.getCenter()[1] - PLAYER_SIZE / 2) <= (platform.getCenter()[1] + platform.getHeight() / 2)) && ((player.getCenter()[1] - PLAYER_SIZE / 2) >= (platform.getCenter()[1] - platform.getHeight() / 2)) && (abs(player.getCenter()[0] - platform.getCenter()[0]) < player.getSize() / 2.0f + platform.getWidth() / 2.0f))
		return true;
	else

		return false;

}


void handleCollision(Player& player, const Platform& platform) {
	/* Implement: collision handling of player */
	if ((isCollisionDetected(player, platform)) && (player.isFalling())) {
		player.setCenter(Vector3f(player.getCenter()[0], platform.getCenter()[1] + PLAYER_SIZE, 0));
		player.setVelocity(Vector3f(0.0f, 0.0f, 0.0f));
		player.setAcceleration(Vector3f(0.0f, 0.0f, 0.0f));
		player.setVerticalState(Player::STOPJ);
	}

}

bool isonfloor(Player& player, const Platform& platform) {
	if (((player.getCenter()[1] - PLAYER_SIZE / 2) == (platform.getCenter()[1] + platform.getHeight() / 2)) && (abs(player.getCenter()[0] - platform.getCenter()[0]) < player.getSize() / 2.0f + platform.getWidth() / 2.0f)) {
		player.setAcceleration(Vector3f(0.0f, 0.0f, 0.0f));
		player.setVerticalState(Player::STOPJ);
		return true;
	}
	else {
		return false;
	}


}

void enemyMove(Enemy& enemy, Platform& platform) {
	if (enemy.getCenter()[0] + PLAYER_SIZE / 2 == platform.getCenter()[0] + platform.getWidth() / 2) {
		enemy.setFace(Enemy::FACE::LEFT);
	}
	else if (enemy.getCenter()[0] - PLAYER_SIZE / 2 == platform.getCenter()[0] - platform.getWidth() / 2) {
		enemy.setFace(Enemy::FACE::RIGHT);
	}
}

void minuslife(Enemy& enemy, Player& player) {
	if (abs(player.getCenter()[0] - enemy.getCenter()[0]) <= 40 && abs(player.getCenter()[1] - enemy.getCenter()[1]) <= 40) {
		player.setCenter(Vector3f(-boundaryX + PLAYER_SIZE * 1.5f, -boundaryY + PLAYER_SIZE * 1.5f, 0.0f));
		life -= 1;
	}
}

void initialize() {
	player.setVerticalState(Player::VERTICAL_STATE::STOPJ);
	player.setAcceleration(Vector3f(0.0f, 0.0f, 0.0f));
	enemy1.setFace(Enemy::FACE::RIGHT);
	enemy2.setFace(Enemy::FACE::LEFT);
	enemy3.setFace(Enemy::FACE::RIGHT);
	enemy21.setFace(Enemy::FACE::LEFT);
	enemy22.setFace(Enemy::FACE::RIGHT);
	enemy23.setFace(Enemy::FACE::LEFT);
	enemy24.setFace(Enemy::FACE::RIGHT);
	enemy25.setFace(Enemy::FACE::LEFT);
	player.initialize();
	enemy1.initialize();
	enemy2.initialize();
	enemy3.initialize();
	enemy21.initialize();
	enemy22.initialize();
	enemy23.initialize();
	enemy24.initialize();
	enemy25.initialize();
	texture1.initializeTexture("Front Image1.png");
	texture2.initializeTexture("Front Image2.png");
	playerf1.initializeTexture("playerL.png");
	playerf2.initializeTexture("playerR.png");
	heart.initializeTexture("life.png");
	gameover.initializeTexture("GAMEOVER.png");
	gameover1.initializeTexture("GAMEOVER1.png");
	ALLCLEAR.initializeTexture("ALLCLEAR.png");
}

void idle() {
	end_t = clock();

	if ((float)(end_t - start_t) > 1000 / 30.0f) {
		player.move();
		if (player.getVelocity()[1] < 0) {
			player.setAcceleration(Vector3f(0.0f, -0.2f, 0.0f));
			player.setVerticalState(Player::VERTICAL_STATE::FALL);
		}

		if (player.getCenter()[0] < -260) {
			player.setCenter(Vector3f(-260, player.getCenter()[1], player.getCenter()[2]));
		}

		if (player.getCenter()[0] > 260) {
			player.setCenter(Vector3f(260, player.getCenter()[1], player.getCenter()[2]));
		}


		if (stage == 1) {
			enemy1.move();
			enemy2.move();
			enemy3.move();

			CollisionHandler(player, bubbles);
			CollisionHandler(enemy1, bubbles);
			CollisionHandler(enemy2, bubbles);
			CollisionHandler(enemy3, bubbles);
			handleCollision(player, ground);
			handleCollision(player, F11);
			handleCollision(player, F12);
			handleCollision(player, F13);
			handleCollision(player, F21);
			handleCollision(player, F22);
			handleCollision(player, F23);
			handleCollision(player, F31);
			handleCollision(player, F32);
			handleCollision(player, F33);
			enemyMove(enemy1, F12);
			enemyMove(enemy2, F22);
			enemyMove(enemy3, F32);
			minuslife(enemy1, player);
			minuslife(enemy2, player);
			minuslife(enemy3, player);
			if (!isonfloor(player, F11) && !isonfloor(player, F12) && !isonfloor(player, F13) && !isonfloor(player, ground) &&
				!isonfloor(player, F21) && !isonfloor(player, F22) && !isonfloor(player, F23) &&
				!isonfloor(player, F31) && !isonfloor(player, F32) && !isonfloor(player, F33)) {
				if (player.isStop()) {
					player.setAcceleration(Vector3f(0, -0.5f, 0));
					player.setVerticalState(Player::VERTICAL_STATE::FALL);
				}
			}
		}
		if (stage == 2) {

			enemy21.move();
			enemy22.move();
			enemy23.move();
			enemy24.move();
			enemy25.move();
			enemyMove(enemy21, F211);
			enemyMove(enemy22, F212);
			enemyMove(enemy23, F222);
			enemyMove(enemy24, F231);
			enemyMove(enemy25, F232);
			minuslife(enemy21, player);
			minuslife(enemy22, player);
			minuslife(enemy23, player);
			minuslife(enemy24, player);
			minuslife(enemy25, player);

			CollisionHandler(enemy21, bubbles);
			CollisionHandler(enemy22, bubbles);
			CollisionHandler(enemy23, bubbles);
			CollisionHandler(enemy24, bubbles);
			CollisionHandler(enemy25, bubbles);
			CollisionHandler(player, bubbles);
			handleCollision(player, ground);
			handleCollision(player, F212);
			handleCollision(player, F211);
			handleCollision(player, F221);
			handleCollision(player, F222);
			handleCollision(player, F223);
			handleCollision(player, F231);
			handleCollision(player, F232);
			if (!isonfloor(player, F211) && !isonfloor(player, F212) && !isonfloor(player, F221) && !isonfloor(player, ground) &&
				!isonfloor(player, F222) && !isonfloor(player, F223) && !isonfloor(player, F231) && !isonfloor(player, F232)) {
				if (player.isStop()) {
					player.setAcceleration(Vector3f(0, -0.5f, 0));
					player.setVerticalState(Player::VERTICAL_STATE::FALL);
				}
			}
		}

		for (int i = 0; i < bubbles.size(); i++) {
			
			bubbles[i].move();
			//버블 크기 조절
			if (bubbles[i].getRadius() < PLAYER_SIZE / 2)
				bubbles[i].setRadius(bubbles[i].getRadius() + 0.5f);
			if (bubbles[i].getRadius() == PLAYER_SIZE / 2)
				bubbles[i].setVelocity(Vector3f(0.0f, 3.0f, 0.0f));
			//버블 y축 이동
			if (bubbles[i].getCenter()[0] + bubbles[i].getRadius() >= boundaryX - PLAYER_SIZE) {
				if (bubbles[i].getRadius() <= 20) {
					bubbles[i].setCenter(Vector3f(260, bubbles[i].getCenter()[1], player.getCenter()[2]));
				}
				bubbles[i].setVelocity(Vector3f(0.0f, 3.0f, 0.0f));
			}
			if (bubbles[i].getCenter()[0] - bubbles[i].getRadius() <= -boundaryX + PLAYER_SIZE) {
				if (bubbles[i].getRadius() <= 20) {
					bubbles[i].setCenter(Vector3f(-260, bubbles[i].getCenter()[1], player.getCenter()[2]));
				}
				bubbles[i].setVelocity(Vector3f(0.0f, 3.0f, 0.0f));
			}
			if (bubbles[i].getcollision() && bubbles[i].getCenter()[1] > 280) {
				bubbles[i].setCenter(Vector3f(bubbles[i].getCenter()[0], 280, bubbles[i].getCenter()[2]));
			}
		}
		for (int i = 0; i < effect.size(); i++) {
			effect[i].move();


		}

		start_t = end_t;

		glutPostRedisplay();
	}
}

void displayCharacters(void* font, string str, float x, float y) {

	glPushMatrix();

	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++) {
		glutBitmapCharacter(font, str[i]);
	}

	glPopMatrix();
}


void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw 2D
	if (enemycount == 0) {
		if (stage == 1 && bubblecount == 0) {
			stage = 2;
			bubbles.clear();

			enemycount = 5;
			player.setCenter(Vector3f(-boundaryX + PLAYER_SIZE * 1.5f, -boundaryY + PLAYER_SIZE * 1.5f, 0.0f));
		}
		else if (stage == 2 && bubblecount == 0) {
			bubbles.clear();
			stage = 3;
		}
		if (stage == 3) {
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D, ALLCLEAR.getTextureID());

			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(-boundaryX / 1.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(-boundaryX / 1.0f, boundaryY - 20.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(boundaryX / 1.0f, boundaryY - 20.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(boundaryX / 1.0f, 0.0f);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D, gameover1.getTextureID());

			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(-190, -200);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(-190, -90);
			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(190, -90);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(190, -200);
			glEnd();

			glDisable(GL_TEXTURE_2D);

		}
	}

	if (life == 0) {
		stage = -1;

		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, gameover.getTextureID());

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-boundaryX / 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-boundaryX / 1.0f, boundaryY - 20.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(boundaryX / 1.0f, boundaryY - 20.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(boundaryX / 1.0f, 0.0f);
		glEnd();

		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, gameover1.getTextureID());

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-190, -200);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-190, -90);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(190, -90);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(190, -200);
		glEnd();

		glDisable(GL_TEXTURE_2D);


	}
	if (stage == 1) {
		ground.draw();
		ground2.draw();
		ground3.draw();
		ground4.draw();
		F11.draw();
		F12.draw();
		F13.draw();
		F21.draw();
		F22.draw();
		F23.draw();
		F31.draw();
		F32.draw();
		F33.draw();
		enemy1.draw();
		enemy2.draw();
		enemy3.draw();
		player.draw();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		if (life >= 1) {
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D, heart.getTextureID());
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(-300, -boundaryY);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(-300, -boundaryY + 40.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(-260, -boundaryY + 40.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(-260, -boundaryY);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
		if (life >= 2) {
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D, heart.getTextureID());
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(-255, -boundaryY);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(-255, -boundaryY + 40.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(-215, -boundaryY + 40.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(-215, -boundaryY);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
		if (life >= 3) {
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D, heart.getTextureID());
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(-210, -boundaryY);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(-210, -boundaryY + 40.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(-170, -boundaryY + 40.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(-170, -boundaryY);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
	}
	if (stage == 2) {

		ground.draw();
		ground2.draw();
		ground3.draw();
		ground4.draw();
		F211.draw();
		F212.draw();
		F221.draw();
		F222.draw();
		F223.draw();
		F231.draw();
		F232.draw();
		enemy21.draw();
		enemy22.draw();
		enemy23.draw();
		enemy24.draw();
		enemy25.draw();
		player.draw();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		if (life >= 1) {
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D, heart.getTextureID());
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(-300, -boundaryY);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(-300, -boundaryY + 40.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(-260, -boundaryY + 40.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(-260, -boundaryY);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
		if (life >= 2) {
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D, heart.getTextureID());
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(-255, -boundaryY);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(-255, -boundaryY + 40.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(-215, -boundaryY + 40.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(-215, -boundaryY);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
		if (life >= 3) {
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D, heart.getTextureID());
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(-210, -boundaryY);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(-210, -boundaryY + 40.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(-170, -boundaryY + 40.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(-170, -boundaryY);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}

	}


	if (stage == 0) {
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, texture1.getTextureID());

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-boundaryX / 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-boundaryX / 1.0f, boundaryY - 20.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(boundaryX / 1.0f, boundaryY - 20.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(boundaryX / 1.0f, 0.0f);
		glEnd();

		glDisable(GL_TEXTURE_2D);
		player1.draw();
		player1.setFace(Player::FACE::RIGHT);
		player2.draw();

		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, texture2.getTextureID());
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-boundaryX / 1.5f, -boundaryY / 2.0f - 50.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-boundaryX / 1.5f, -boundaryY / 2.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(boundaryX / 1.5f, -boundaryY / 2.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(boundaryX / 1.5f, -boundaryY / 2.0f - 50.0f);
		glEnd();

		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, playerf2.getTextureID());
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(player1.getCenter()[0] - PLAYER_SIZE, player1.getCenter()[1] - PLAYER_SIZE);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(player1.getCenter()[0] - PLAYER_SIZE, player1.getCenter()[1] + PLAYER_SIZE);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(player1.getCenter()[0] + PLAYER_SIZE, player1.getCenter()[1] + PLAYER_SIZE);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(player1.getCenter()[0] + PLAYER_SIZE, player1.getCenter()[1] - PLAYER_SIZE);
		glEnd();

		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, playerf1.getTextureID());
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(player2.getCenter()[0] - PLAYER_SIZE, player2.getCenter()[1] - PLAYER_SIZE);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(player2.getCenter()[0] - PLAYER_SIZE, player2.getCenter()[1] + PLAYER_SIZE);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(player2.getCenter()[0] + PLAYER_SIZE, player2.getCenter()[1] + PLAYER_SIZE);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(player2.getCenter()[0] + PLAYER_SIZE, player2.getCenter()[1] - PLAYER_SIZE);
		glEnd();

		glDisable(GL_TEXTURE_2D);

	}

	// Draw 3D
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(light.getID());
	light.draw();

	for (int i = 0; i < bubbles.size(); i++) {
		if (stage != -1) {
			bubbles[i].draw();
		}
	}

	for (int i = 0; i < effect.size(); i++) {
		effect[i].draw();


	}

	glDisable(light.getID());
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();
}

void keyboardDown(unsigned char key, int x, int y) {

	switch (key)
	{
	case ' ':
		//glutLeaveMainLoop();
		if (stage == 0)
			stage = 1;
		else {
			bubbles.push_back(player.shootBubble());
		}
		break;
	case 27:
		if (life == 0 || (stage == 2 && enemycount == 0)) {
			glutLeaveMainLoop();
		}
		break;
	case 'R':
	case 'r':
		if (life == 0 || enemycount == 0) {

			life = 3;
			stage = 0;
			enemycount = 3;
			player.setCenter(Vector3f(-boundaryX + PLAYER_SIZE * 1.5f, -boundaryY + PLAYER_SIZE * 1.5f, 0.0f));
			player.setVelocity(Vector3f(0, 0, 0));
			player.setAcceleration(Vector3f(0, 0, 0));
			enemy1.setCenter(Vector3f(0, -130, 0));
			enemy2.setCenter(Vector3f(0, 0, 0));
			enemy3.setCenter(Vector3f(0, 130, 0));
			enemy1.setFace(Enemy::FACE::LEFT);
			enemy2.setFace(Enemy::FACE::RIGHT);
			enemy3.setFace(Enemy::FACE::LEFT);
			enemy21.setCenter(Vector3f(-120, -130, 0));
			enemy22.setCenter(Vector3f(120, -130, 0));
			enemy23.setCenter(Vector3f(0, 0, 0));
			enemy24.setCenter(Vector3f(-120, 130, 0));
			enemy25.setCenter(Vector3f(120, 130, 0));
			enemy21.setFace(Enemy::FACE::LEFT);
			enemy22.setFace(Enemy::FACE::RIGHT);
			enemy23.setFace(Enemy::FACE::LEFT);
			enemy24.setFace(Enemy::FACE::RIGHT);
			enemy25.setFace(Enemy::FACE::LEFT);
			bubblecount = 0;
			bubbles.clear();
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
	case GLUT_KEY_UP:
		if (player.isStop()) {
			player.setVerticalState(Player::VERTICAL_STATE::JUMP);
			player.setVelocity(Vector3f(0, 12, 0));
			player.setAcceleration(Vector3f(0, -0.5f, 0));

		}

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
		player.setVelocity(Vector3f(0.0f, player.getVelocity()[1], 0));
		break;
	case GLUT_KEY_LEFT:
		player.setHorizontalState(Player::HORIZONTAL_STATE::STOP);
		player.setVelocity(Vector3f(0.0f, player.getVelocity()[1], 0));
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	// init GLUT and create Window

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

	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(specialKeyUp);

	//glutTimerFunc(1000, togglePl, 1);
	// enter GLUT event processing cycle
	glutMainLoop();
	return 0;


}
