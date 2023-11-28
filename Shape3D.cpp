#include "Shape3D.h"

Shape3D::Shape3D() {

}

Shape3D::Shape3D(float x, float y, float z)
{
	center[0] = x;
	center[1] = y;
	center[2] = z;
}

void Shape3D::setCenter(const Vector3f& c) {
	center = c;
}

Vector3f Shape3D::getCenter() const {
	return center;
}

void Shape3D::setVelocity(const Vector3f& v) {
	velocity = v;
}

Vector3f Shape3D::getVelocity() const {
	return velocity;
}

void Shape3D::setAcceleration(const Vector3f& a) {
    acceleration = a;
}

Vector3f Shape3D::getAcceleration() const {
    return acceleration;
}

void Shape3D::setRandomVelocity() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disX(-10.0f, 10.0f);
    std::uniform_real_distribution<float> disY(0.0f, 10.0f);

    float x = disX(gen);
    float y = disY(gen);
    setVelocity(Vector3f(x, y, 0));
}

void Shape3D::setRandomMaterial() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disColor(0.0f, 1.0f);

    float r = disColor(gen);
    float g = disColor(gen);
    float b = disColor(gen);
    float a = disColor(gen);
    mtl.setAmbient(r, g, b, a);
}

void Shape3D::move() {
	velocity = velocity + acceleration;
	center = center + velocity;
}
