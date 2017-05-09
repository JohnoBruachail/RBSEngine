#include "Shape.h"

//create box
Shape::Shape(float MaxX, float MaxY, float MinX, float MinY)
{
	maxX = MaxX;
	maxY = MaxY;
	minX = MinX;
	minY = MinY;
}

//create circle
Shape::Shape(float Radius)
{
	radius = Radius;
}

void Shape::Update(float velocityX ,float velocityY)
{
	maxX += velocityX;
	maxY += velocityY;
	minX += velocityX;
	minY += velocityY;
}

Shape::~Shape()
{
}

