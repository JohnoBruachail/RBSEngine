#include <vector>
#include <cmath>
#include "Vector2D.h"

using namespace std;

class Shape
{
public:

	float maxX;
	float maxY;
	float minX;
	float minY;
	float radius;
	//creates the shape to draw onscreen using SDL, this also creates the physics frame to surround the object
	Shape(float radius);
	Shape(float maxX, float maxY, float minX, float minY);
	void Update(float, float);
	~Shape();
	
};

