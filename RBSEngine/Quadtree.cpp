#include "Quadtree.h"

Quadtree::Quadtree(float X, float Y, float Width, float Height, Frame* StoredFrame)
{
	x = X;
	y = Y;
	width = Width;
	height = Height;

	storedFrames[0] = StoredFrame;
	storedFrames[1] = NULL;
	storedFrames[2] = NULL;
	storedFrames[3] = NULL;
	storedFrames[4] = NULL;
	storedFrames[5] = NULL;
	storedFrames[6] = NULL;
	storedFrames[7] = NULL;
	storedFrames[8] = NULL;
	storedFrames[9] = NULL;
	isLeaf = true;
}

Quadtree::~Quadtree(void)
{

}

void Quadtree::Clear(void)
{
	for(int i = 0; i < 10; i++){
		storedFrames[i] = NULL;
	}
	isLeaf = true;

	NW->~Quadtree();
	NE->~Quadtree();
	SW->~Quadtree();
	SE->~Quadtree();

}

void Quadtree::AddFrame(Frame& StoredFrame)
{
	if(storedFrames[9] == NULL){
		for(int i = 0; i < 10; i++)
		{
			if(storedFrames[i] == NULL)
			{
				storedFrames[i] = &StoredFrame;
				return;
			}
		}
	}
	else if(storedFrames[9] != NULL)
	{
		Partition(storedFrames, &StoredFrame);
		for(int i = 0; i < 10; i++){
		storedFrames[i] = NULL;
	}
		isLeaf = false;
	}
}

void Quadtree::Partition(array<Frame*,10> StoredFrames, Frame* StoredFrame)
{

	NW = new Quadtree(x, y, width / 2.0f, height / 2.0f, NULL);
	NE = new Quadtree(x + width / 2.0f, y, width / 2.0f, height / 2.0f, NULL);
	SW = new Quadtree(x, y + height / 2.0f, width / 2.0f, height / 2.0f, NULL);
	SE = new Quadtree(x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f, NULL);
	//decide where the two frames go
	for(int i = 0; i < 10; i++){
		sortedFrames[i] = Sort(StoredFrames[i]);
	}
	sortedFrames[10] = Sort(StoredFrame);
	
	for(int i = 0; i <= 9; i++){
		if(sortedFrames[i] == 1){NW->AddFrame(*StoredFrames[i]);}
		if(sortedFrames[i] == 2){NE->AddFrame(*StoredFrames[i]);}
		if(sortedFrames[i] == 3){SW->AddFrame(*StoredFrames[i]);}
		if(sortedFrames[i] == 4){SE->AddFrame(*StoredFrames[i]);}
	}

	if(sortedFrames[10] == 1){NW->AddFrame(*StoredFrame);}
	else if(sortedFrames[10] == 2){NW->AddFrame(*StoredFrame);}
	else if(sortedFrames[10] == 3){NW->AddFrame(*StoredFrame);}
	else if(sortedFrames[10] == 4){NW->AddFrame(*StoredFrame);}
	return;
}

int Quadtree::Sort(Frame* ThisFrame)
{
	if(ThisFrame->position.x < width / 2.0f && ThisFrame->position.y > height / 2.0f){
		return 1;
	}
	else if(ThisFrame->position.x > width / 2.0f && ThisFrame->position.y > height / 2.0f){
		return 2;
	}
	else if(ThisFrame->position.x < width / 2.0f && ThisFrame->position.y < height / 2.0f){
		return 3;
	}
	else if(ThisFrame->position.x > width / 2.0f && ThisFrame->position.y < height / 2.0f){
		return 4;
	}
	return 0;
}

void Quadtree::Search(list<Couple>* CouplesList){

	if(isLeaf == true)
	{
		for(int i = 0; i < 10; i++)
		{
			if(storedFrames[i] != NULL)
			{
				newCouple.a = storedFrames[i];

				for(int p = 0; p < 10; p++)
				{
					if(storedFrames[p] != NULL && p != i && p > i)
					{
						newCouple.b = storedFrames[p];
						CouplesList->push_back(newCouple);
					}
				}

			}
		}
	}
	else{
		NW->Search(CouplesList);
		NE->Search(CouplesList);
		SW->Search(CouplesList);
		SE->Search(CouplesList);
	}
}