#include "CollisionRestitution.h"

CollisionRestitution::CollisionRestitution(Frame a, Frame b)
{
	//cannot - as the data types are not included in math librarys, maybe use normal math vectors
	//Vector2D relativeVelocity = a.velocity - b.velocity;


	////find the relative velocity in terms of the normal direction
	//float velocityAlongNormal = DotProduct(relativeVelocity, normal)

	////restitution
	//float e - min(a.restitution, b.restitution);

	//float j = 1(1+e) * velocityAlongNormal;
	//j /= 1 /a.mass + 1/ b.mass;

	////apply impulse to both objects
	//Vector2D impulse = j * normal;
	//a.velocity -= 1 /a.mass * impulse;
	//b.velocity -= 1 /b.mass * impulse;




}


CollisionRestitution::~CollisionRestitution()
{
}
