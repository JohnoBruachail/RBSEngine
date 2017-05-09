#include "Frame.h"

Frame::Frame(float MaxX, float MaxY, float MinX, float MinY, float PosX, float PosY, Material Material, int Mass)
{
	shapeType = 1;//1 for box
	position.Set(PosX, PosY);
	velocity.Set(0, 0);
	angularVelocity = 0;
	torque = 0;
	//orientation = Random( -PI, PI );
	force.Set(0, 0);
	staticFriction = 0.5f;
	dynamicFriction = 0.3f;
	restitution = 0.2f;
	material = Material;
	mass = Mass;
	shape = new Shape(MaxX, MaxY, MinX, MinY);
}

Frame::Frame(float Radius, float PosX, float PosY, Material Material, int Mass)
{
	shapeType = 2;//2 for circle
	position.Set(PosX, PosY);
	velocity.Set(0, 0);
	angularVelocity = 0;
	torque = 0;
	//orientation = Random( -PI, PI );
	force.Set(0, 0);
	staticFriction = 0.5f;
	dynamicFriction = 0.3f;
	restitution = 0.2f;
	material = Material;
	mass = Mass;
	shape = new Shape(Radius);
}

Frame::~Frame()
{
}

void Frame::Update()
{
	if(mass > 0 && mass < 10){
		velocity.y -= GRAVITY;
	}

	position.x += velocity.x;
	position.y += velocity.y;

	shape->Update(velocity.x, velocity.y);
}