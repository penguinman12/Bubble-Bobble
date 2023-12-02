#include "Bubble.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <GL/freeglut.h>

Bubble::Bubble() {
	radius = 1.0f;
	slice = stack = 10;

	center = Vector3f(0.0f, 0.0f, 0.0f);
	velocity = Vector3f(0.0f, 0.0f, 0.0f);

	mtl.setEmission(0.1f, 0.1f, 0.1f, 1.0f);
	mtl.setAmbient(0.529f, 0.808f, 0.980f, 1.0f);
	mtl.setDiffuse(0.5f, 0.5f, 0.5f, 1.0f);
	mtl.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
	mtl.setShininess(10.0f);
}

Bubble::Bubble(float r, int sl, int st) {
	radius = r;
	slice = sl;
	stack = st;

	center = Vector3f(0.0f, 0.0f, 0.0f);
	velocity = Vector3f(0.0f, 0.0f, 0.0f);

	mtl.setEmission(0.1f, 0.1f, 0.1f, 1.0f);
	mtl.setAmbient(0.529f, 0.808f, 0.980f, 1.0f);
	mtl.setDiffuse(0.5f, 0.5f, 0.5f, 1.0f);
	mtl.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
	mtl.setShininess(10.0f);
}

void Bubble::setRadius(float r) {
	radius = r;
}

float Bubble::getRadius() const {
	return radius;
}

void Bubble::setSlice(int sl) {
	slice = sl;
}

void Bubble::setStack(int st) {
	stack = st;
}

void Bubble::setCenter(const Vector3f& c) {
	center = c;
}

Vector3f Bubble::getCenter() const {
	return center;
}

void Bubble::setVelocity(const Vector3f& v) {
	velocity = v;
}

Vector3f Bubble::getVelocity() const {
	return velocity;
}

void Bubble::setcollision(int c){
	collision = c;
}
bool Bubble::getcollision() {
	return collision;
}

void Bubble::setMTL(const Material& m) {
	mtl.setEmission(m.getEmission()[0], m.getEmission()[1], m.getEmission()[2], m.getEmission()[3]);
	mtl.setAmbient(m.getAmbient()[0], m.getAmbient()[1], m.getAmbient()[2], m.getAmbient()[3]);
	mtl.setDiffuse(m.getDiffuse()[0], m.getDiffuse()[1], m.getDiffuse()[2], m.getDiffuse()[3]);
	mtl.setSpecular(m.getSpecular()[0], m.getSpecular()[1], m.getSpecular()[2], m.getSpecular()[3]);
	mtl.setShininess(m.getShininess());
}

void Bubble::move() {
	center = center + velocity;
}

void Bubble::draw() const {
	glPushMatrix();

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, &mtl.getEmission()[0]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, &mtl.getAmbient()[0]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &mtl.getDiffuse()[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &mtl.getSpecular()[0]);
	glMaterialf(GL_FRONT, GL_SHININESS, mtl.getShininess());

	glTranslatef(center[0], center[1], center[2]);
	glutSolidSphere(radius, slice, stack);
	glPopMatrix();     
}

void Bubble::RandomMaterial(){
	radius = 1.0f;
	slice = stack = 10;
	mtl.setAmbient((rand() % 10) / 10.0 + 0.1, (rand() % 10) / 10.0 + 0.1, (rand() % 10) / 10.0 + 0.1, (rand() % 10) / 10.0);
	mtl.setDiffuse((rand() % 10) / 10.0 + 0.1, (rand() % 10) / 10.0, (rand() % 10) / 10.0 + 0.1, (rand() % 10) / 10.0);
	mtl.setEmission((rand() % 10) / 10.0 + 0.1, (rand() % 10) / 10.0 + 0.1, (rand() % 10) / 10.0, (rand() % 10) / 10.0);
	mtl.setSpecular((rand() % 10) / 10.0 + 0.1, (rand() % 10) / 10.0 + 0.1, (rand() % 10) / 10.0, (rand() % 10) / 10.0);
	mtl.setShininess((rand() % 10) / 10.0 + 0.1);
}

void Bubble::RandomVelocity() {
	velocity[0] = (rand() % 10);
	velocity[1] = (rand() % 10);
	velocity[2] = (rand() % 10);

}

