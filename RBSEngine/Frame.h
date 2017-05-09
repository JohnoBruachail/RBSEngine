#include <iostream>
#include "Shape.h"
#include "Material.h"
#include "Vector2D.h"

#pragma once
class Frame
{
public:
	//creates a frame around a shape drawn on screen, allows the shape to have applied physics properties and be taking into accounc on copllisions as the game is running
	int shapeType;
	Vector2D position, velocity, force;
	float angularVelocity, torque, orientation;// radians

	// Set by shape
	float I;  // moment of inertia
	float iI; // inverse inertia
	float m;  // mass
	float im; // inverse masee

	float staticFriction, dynamicFriction, restitution;

	struct Transform{ float posX; float posY; };

	Material material;
	Shape* shape;
	int mass;

	Frame();
	Frame(float, float, float, float, float, float, Material, int);
	Frame(float, float, float, Material, int);
	~Frame();
	void Update();

};

