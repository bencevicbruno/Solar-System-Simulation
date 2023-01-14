#pragma once

class Vector
{
public:
	float x, y, z, w;

	Vector();
	Vector(float constant);
	Vector(float x, float y, float z, float w);

	Vector operator+(const Vector& other) const;
	Vector operator-(const Vector& other) const;
	Vector operator*(float constant) const;
	Vector operator/(float constant) const;

	Vector& operator+=(const Vector& other);
	Vector& operator-=(const Vector& other);
	Vector& operator*=(float constant);
	Vector& operator/=(float constant);

	float length() const;
	float length2() const;

	void normalize();

	static float DotProduct(const Vector& first, const Vector& second);
	static Vector CrossProduct(const Vector& first, const Vector& second);

	static Vector up();
	static Vector down();
	static Vector north();
	static Vector east();
	static Vector south();
	static Vector west();
	static Vector FromPolar(float radius, float yaw, float pitch);
	static Vector CreateRandom(float min, float max);
};