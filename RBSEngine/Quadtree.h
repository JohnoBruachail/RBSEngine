#include "Frame.h"
#include "Couples.h"
#include <array>
#include <list>
#pragma once
//#define maxFrames = 5;
class Quadtree
{
public:
	//creates a quadtree used to store all frame information, this limits the checks for collisions to objects near eachother in the tree increasing the effecency of all of the engine.
	float x, y, width, height;
	int maxObjects, sortedFrames[11];
	bool isLeaf;//is this a leaf node
	//struct Couple{ Frame* a; Frame* b; };
	struct Couple newCouple;
	array<Frame*,10> storedFrames;

	Quadtree* NW;
	Quadtree* NE;
	Quadtree* SW;
	Quadtree* SE;

	Quadtree(float, float, float, float, Frame*);
	~Quadtree();

	void Clear();
	void AddFrame(Frame&);
	void Partition(array<Frame*,10>, Frame*);
	int Sort(Frame*);
	void Search(list<Couple>*);
};