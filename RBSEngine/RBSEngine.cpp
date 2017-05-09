#include "RBSEngine.h"


RBSEngine::RBSEngine()//you would naturally input the games measurements when you call the engine
{
 
	gameTree = new Quadtree(0, 0, 1200, 800, NULL);//a constantly updated quadtree used to generate couples
}

RBSEngine::~RBSEngine()
{
}

void RBSEngine::CreateFrame(float MaxX, float MaxY, float MinX, float MinY, float PosX, float PosY, Material Material, int Mass)
{
	//makes a frame
	Frame newframe(MaxX, MaxY, MinX, MinY, PosX, PosY, Material, Mass);
	//adds to linked list
	frameList.push_back(newframe);
	//after a frame is created update the quadtree
}

void RBSEngine::CreateFrame(float Radius, float PosX, float PosY, Material Material, int Mass)
{
	//makes a frame
	Frame newframe(Radius, PosX, PosY,  Material, Mass);
	//adds to linked list
	frameList.push_back(newframe);

	//after a frame is created update the quadtree
}

void RBSEngine::DeleteFrame()
{
	//see list commands remove frame if conditions meet
	//runs threw linked list
	//removes frame
}

void RBSEngine::Update()
{
	gameTree->Clear();
	//UPDATE OPJECTS BY THERE POSITION FIRST.
	
	for(list<Frame>::iterator it = frameList.begin(); it != frameList.end(); it++){
		it->Update();
	}
	
	//populate the quadtree
	for(list<Frame>::iterator it = frameList.begin(); it != frameList.end(); it++){
		gameTree->AddFrame(*it);
	}

	//run Broadphase Collision Detection to generate couples
	GenerateCouples();
	
	for(list<Couple>::iterator listIt = couples.begin(); listIt != couples.end(); listIt++)
	{
		//run narrowCollisionDetection confirm collisions
		CollisionCheck(listIt);
	}
}

void RBSEngine::GenerateCouples()
{
	//clear couples
	couples.clear();

	gameTree->Search(&couples);
	
	//go threw each frame and create couple with other frames in boxes next to it in quadtree
	//dont add duplicates to couples list
	//send couples to collision check to check for collisions
}

void RBSEngine::CollisionCheck(list<Couple>::iterator Couple)
{
	//if box shape collides with box shape
	if(Couple->a->shapeType == 1 && Couple->a->shapeType == 1)
	{	
		if(Couple->a->shape->maxX < Couple->b->shape->minX || Couple->a->shape->minX > Couple->b->shape->maxX || Couple->a->shape->maxY < Couple->b->shape->minY || Couple->a->shape->minY > Couple->b->shape->maxY) return;
		
		//if an intersection is found an overlapp has occured therefore call collision resolution to resolve collisions
		else{CollisionResolution(Couple);};
	}
	
	//if circle shape collides with circle shape
	else if(Couple->a->shapeType == 2 && Couple->a->shapeType == 2)
	{
		float r = Couple->a->shape->radius + Couple->b->shape->radius;
		r *= r;

		(Couple->a->position.x - Couple->b->position.x)*(Couple->a->position.x - Couple->b->position.x)
		+ (Couple->a->position.y - Couple->b->position.y)*(Couple->a->position.y - Couple->b->position.y);

		distance = sqrt((Couple->a->position.x - Couple->b->position.x)*(Couple->a->position.x - Couple->b->position.x) +	
						(Couple->a->position.y - Couple->b->position.y)*(Couple->a->position.y - Couple->b->position.y));
		
		if(r < distance){return;}
			else{CollisionResolution(Couple);
		}
	}

	//if one shape is circle and the other is a box
	else if(Couple->a->shapeType == 1 && Couple->a->shapeType == 2 || Couple->a->shapeType == 2 && Couple->a->shapeType == 1)
	{

	}
}

void RBSEngine::CollisionResolution(list<Couple>::iterator Couple)
{
	//box vs box
	if(Couple->a->shapeType == 1 && Couple->b->shapeType == 1){
		
		relativeVelocity = Couple->b->velocity - Couple->a->velocity;

        if(Couple->b->velocity.x < 0.0f)
        {
			//right
			normal.x = 1.0f;
            normal.y = 0.0f;
			penDepth = fabs(Couple->b->shape->minX - Couple->a->shape->maxX);
			Couple->b->position.x += penDepth;
			Couple->b->shape->maxX += (penDepth+1);
			Couple->b->shape->minX += (penDepth+1);
        }
	    else if(Couple->b->velocity.x > 0.0f)
        {
			//left
			normal.x = -1.0f;
		    normal.y = 0.0f;
			penDepth = fabs(Couple->a->shape->minX - Couple->b->shape->maxX);
			Couple->b->position.x -= penDepth;
			Couple->b->shape->maxX -= (penDepth+1);
			Couple->b->shape->minX -= (penDepth+1);
        }
        if(Couple->b->velocity.y < 0.0f)
        {
			//below
            normal.x = 0.0f;
            normal.y = 1.0f;
			penDepth = fabs(Couple->b->shape->maxY - Couple->a->shape->minY);
			Couple->b->position.y += penDepth;
			Couple->b->shape->maxY += (penDepth+1);
			Couple->b->shape->minY += (penDepth+1);
        }
	    else if(Couple->b->velocity.y > 0.0f)
        {
			//above
            normal.x = 0.0f;
            normal.y = -1.0f;
			penDepth = fabs(Couple->a->shape->minY - Couple->b->shape->maxY);
			Couple->b->position.y -= (penDepth+1);
			Couple->b->shape->maxY -= (penDepth+1);
			Couple->b->shape->minY -= (penDepth+1);
        }

		velAlongNormal = ((relativeVelocity.x * normal.x) + (relativeVelocity.y * normal.y));
		// Do not resolve if velocities are separating
		if(velAlongNormal > 0){return;}
		// Calculate restitution
		e = min(Couple->a->restitution, Couple->b->restitution);
		// Calculate impulse scalar
		j = -(1 + e) * velAlongNormal;

		if(Couple->a->mass == 0)
		{
			Couple->b->velocity = -Couple->b->velocity;
		}
		else if(Couple->b->mass == 0)
		{
			Couple->a->velocity = -Couple->a->velocity;
		}
		else
		{
			j /= 1 / Couple->a->mass + 1 / Couple->b->mass;
 
			// Apply impulse
			impulse = normal * j;

			totalMass =  Couple->a->mass + Couple->b->mass;
			ratio = Couple->a->mass / totalMass;
			Couple->a->velocity -= ratio * impulse;
 
			ratio = Couple->b->mass / totalMass;
			Couple->b->velocity += ratio * impulse;
		}



		

	}

	//circle vs circle
	else if(Couple->a->shapeType == 2 && Couple->b->shapeType == 2){
	
		relativeVelocity = Couple->b->velocity - Couple->a->velocity;
		velAlongNormal = ((relativeVelocity.x * normal.x) + (relativeVelocity.y * normal.y));
		
		// Do not resolve if velocities are separating
		if(velAlongNormal > 0){return;}

		// Calculate restitution
		e = min(Couple->a->restitution, Couple->b->restitution);
		
		// Calculate impulse scalar
		j = -(1 + e) * velAlongNormal;
		j /= 1 / Couple->a->mass + 1 / Couple->b->mass;
 
		// Apply impulse
		impulse = j * normal;
		Couple->a->velocity -= 1 / Couple->a->mass * impulse;
		Couple->b->velocity += 1 / Couple->b->mass * impulse;
	}

	else if(Couple->a->shapeType == 1 && Couple->b->shapeType == 2 || Couple->b->shapeType == 2 && Couple->a->shapeType == 1){
	// Calculate relative velocity

	relativeVelocity = Couple->b->velocity - Couple->a->velocity;
	// Calculate relative velocity in terms of the normal direction
	velAlongNormal = ((relativeVelocity.x * normal.x) + (relativeVelocity.y * normal.y));
 
	// Do not resolve if velocities are separating
	if(velAlongNormal > 0){return;}
 
	// Calculate restitution
	e = min(Couple->a->restitution, Couple->b->restitution);
 
	// Calculate impulse scalar
	j = -(1 + e) * velAlongNormal;
	j /= 1 / Couple->a->mass + 1 / Couple->b->mass;
 
	// Apply impulse
	impulse = j * normal;
	Couple->a->velocity -= 1 / Couple->a->mass * impulse;
	Couple->b->velocity += 1 / Couple->b->mass * impulse;
	}

}