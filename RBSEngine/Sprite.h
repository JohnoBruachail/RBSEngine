#ifndef SPRITE_H
#define SPRITE_H

#include "Debug.h"
#include "RBSEngine.h"

#include <SDL_image.h>
#include <string>
#include <iostream>

using namespace std;

class Sprite
{
public:
	Sprite(RBSEngine*, int, int, int, int, int, int, Material, int);//constructor for sprite to be used in simulation, this creates the visible rectangles onscreen
	~Sprite();
 
public:
	bool fixed;
	Material test;//test place materals
	SDL_Rect sprite;//the sdl rectangle
};
#endif
