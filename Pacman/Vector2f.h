#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <math.h> 

class Vector2f
{
public:
	Vector2f()
	{
		x = 0.f;
		y = 0.f;
	}

	Vector2f(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	const Vector2f Vector2f::operator-(const Vector2f &other) const 
	{
		return Vector2f (x - other.x, y - other.y);;
	}

	const Vector2f Vector2f::operator+(const Vector2f &other) const 
	{
		return Vector2f (x + other.x, y + other.y);
	}

	
	const Vector2f Vector2f::operator*(const Vector2f& other) const 
	{
		return Vector2f (x * other.x, y * other.y);
	}

	Vector2f& Vector2f::operator+=(const Vector2f &other) 
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2f& Vector2f::operator*=(const float value) 
	{
		x *= value;
		y *= value;

		return *this;
	}

	Vector2f& Vector2f::operator/=(const float value) 
	{
		x /= value;
		y /= value;

		return *this;
	}

	const Vector2f Vector2f::operator*(const float value) const 
	{
		return Vector2f (x * value, y * value);
	}

	const bool Vector2f::operator==(const Vector2f other) const 
	{
		return this->x == other.x && this->y == other.y;
	}

	float Vector2f::Length() const
	{
		return (float) sqrt(x * x + y * y);
	}

	void Vector2f::Normalize()
	{
		float length = Length();

		if (length > 0.f)
			*this /= length;
	}

	void Vector2f::Inverse() {
		x *= -1;
		y *= -1;
	}

	float x;
	float y;
};

#endif // VECTOR2F_H