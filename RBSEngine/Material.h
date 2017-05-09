#pragma once
class Material
{
public:
	Material();
	~Material();
	//defines what materal the object is made out of, this changes eleasticity, density, restitution 
	struct MaterialType{float density; float restitution;};

	MaterialType Metal;
	MaterialType Rubber;
	MaterialType Static;
	MaterialType Stone;
	MaterialType Wood;
	
	






};

