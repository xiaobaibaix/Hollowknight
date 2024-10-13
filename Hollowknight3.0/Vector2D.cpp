#include "Vector2D.h"

#include <cmath>

Vector2D Vector2D::operator+(const Vector2D& vec) const {
	return Vector2D::Vector2D(x + vec.x, y + vec.y);
}

void Vector2D::operator+=(const Vector2D& vec) {
	x += vec.x, y += vec.y;
}

Vector2D Vector2D::operator-(const Vector2D& vec) const {
	return Vector2D(x - vec.x, y - vec.y);
}

void Vector2D::operator-=(const Vector2D& vec) {
	x -= vec.x, y -= vec.y;
}

//µã»ý

float Vector2D::operator*(const Vector2D& vec) const {
	return x * vec.x + y * vec.y;
}

Vector2D Vector2D::operator*(float val) const {
	return Vector2D(x * val, y * val);
}

void Vector2D::operator*=(float val) {
	x *= val;
	y *= val;
}

float Vector2D::length() {
	return sqrt(x * x + y * y);
}

Vector2D Vector2D::normalize() {
	float len = length();

	if (len == 0) {
		return Vector2D(0, 0);
	}
	return Vector2D(x / len, y / len);
}
