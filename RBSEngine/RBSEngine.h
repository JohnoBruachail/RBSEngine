#include <numeric>

#include "Frame.h"
#include "Quadtree.h"
#include "Couples.h"
#include "Vector2D.h"

#pragma once
class RBSEngine
{
public://creates the physics engine containing all calculations and functions for running in a 2D envirnement
	list<Frame> frameList;
	list<Couple> couples;
	Quadtree* gameTree;
	float distance, rVelocity, vAlongNormal, penDepth, left, top, right, bottom, xEntry, yEntry, xExit, yExit, entryTime, exitTime, velAlongNormal, e, j, totalMass, ratio;
	Vector2D normal, impulse, relativeVelocity;

	RBSEngine();
	~RBSEngine();
	void CreateFrame(float, float, float, float, float, float, Material, int);
	void CreateFrame(float, float, float, Material, int);
	void DeleteFrame();
	void Update();
	void GenerateCouples();
	void CollisionCheck(list<Couple>::iterator);
	void CollisionResolution(list<Couple>::iterator);
};