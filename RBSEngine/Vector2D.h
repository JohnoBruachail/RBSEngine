#ifndef Vector2D_H
#define Vector2D_H

//found here is my own defined type vector2D that creates a vector storing 2 float numbers

#include <cmath> // abs, sqrt
#include <cassert> // assert
#include <algorithm> // max, min

typedef float number;

//constants usually found in physics simulations
const float PI = 3.141592741f;
const float EPSILON = 0.0001f;
const float GRAVITY = -0.00001f;

struct Vector2D
{
	//union used here to store the vector stats in the same area in memory
	union
	{
		number m[1][1], v[2];

		struct
		{
			number x, y;
		};
	};
	
	Vector2D(){}
	Vector2D(number X, number Y): x(X), y(Y){}
	
	void Set(number X, number Y)//sets a vector on input
	{
		x = X;
		y = Y;
	}
	
	//below you should find various operator definitions defining what should occure if the piticular operator symbol is used in conjunction with this vector2D type
	//minus both vector values
	Vector2D operator-(void) const
	{
		return Vector2D(-x, -y);
	}
	//multiplies both vector values
	Vector2D operator*(number V) const
	{
		return Vector2D(x * V, y * V);
	}
	//devides both vector values
	Vector2D operator/(number V) const
	{
		return Vector2D(x / V, y / V);
	}
	//multiplies both vector values by the input factor
	void operator*=(number V)
	{
		x *= V;
		y *= V;
	}
	//adds two vector's together
	Vector2D operator+(const Vector2D& P) const
	{
		return Vector2D(x + P.x, y + P.y);
	}
	//adds two vector's to an input value
	Vector2D operator+(number V) const
	{
		return Vector2D(x + V, y + V);
	}
	
	void operator+=(const Vector2D& P)
	{
		x += P.x;
		y += P.y;
	}
	
	Vector2D operator-(const Vector2D& P) const
	{
		return Vector2D(x - P.x, y - P.y);
	}
	
	void operator-=(const Vector2D& P)
	{
		x -= P.x;
		y -= P.y;
	}

	bool operator==(const Vector2D& P)
	{
		if(x == P.x && y == P.y){return true;}
		else return false;
	}
	
	number LenSqr() const
	{
		return x * x + y * y;
	}
	
	number Len() const
	{
		return std::sqrt( x * x + y * y );
	}
	
	void Rotate(number Radians)
	{
		number c = std::cos(Radians);
		number s = std::sin(Radians);

		number xp = x * c - y * s;
		number yp = x * s + y * c;

		x = xp;
		y = yp;
	}
	
	void Normalize()
	{
		number len = Len( );
		if(len > EPSILON)
		{
			number invLen = 1.0f / len;
			x *= invLen;
			y *= invLen;
		}
	}
};

inline Vector2D operator*(float P, const Vector2D& V)
{
  return Vector2D( P * V.x, P * V.y );
}

inline Vector2D operator/(int P, const Vector2D& V)
{
  return Vector2D( P * V.x, P * V.y );
}
#endif