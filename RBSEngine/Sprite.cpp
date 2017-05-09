#include "Sprite.h"

Sprite::Sprite(RBSEngine* PhysicsEngine, int MaxX, int MaxY, int MinX, int MinY, int MousePosX, int MousePosY, Material Material, int mass)
{	
	sprite.w = MaxX - MinX;
	sprite.h = MaxY - MinY;
	sprite.x = MousePosX - sprite.w/2;
	sprite.y = MousePosY - sprite.h/2;

	if(mass == -1)
	{
		fixed = true;
	}

	PhysicsEngine->CreateFrame((float)MousePosX+(sprite.w/2), (float)MousePosY+(sprite.h/2), (float)MousePosX-(sprite.w/2), (float)MousePosY-(sprite.h/2), (float)MousePosX, (float)MousePosY, Material, mass);
}

Sprite::~Sprite(void)
{

}