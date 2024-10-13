#pragma once
class Vector2D {
public:

	float x;
	float y;

public:
	Vector2D()=default;
	~Vector2D()= default;

	Vector2D(float x,float y):x(x),y(y){}

	Vector2D operator+(const Vector2D& vec)const;

	void operator+=(const Vector2D& vec);

	Vector2D operator-(const Vector2D& vec)const;

	void operator-=(const Vector2D& vec);
	//µã»ý
	float operator*(const Vector2D& vec)const;

	Vector2D operator*(float val)const;

	void operator*=(float val);

	float length();

	Vector2D normalize();
};