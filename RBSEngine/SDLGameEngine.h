#include <iostream>
#include <SDL.h>

#include "Debug.h"
#include "RBSEngine.h"
#include "Sprite.h"

using namespace std;

class SDLGameEngine
{
public:
	//constructor and destructor for the game class
	SDLGameEngine(const char*, int, int, int, int, int);
	~SDLGameEngine();

	//three main event handlers used to handle keypresses from player depending on the state of the game
	//i would have prefered to only have one but due to time constraints had to rush these out
	void HandleEvents();
	void Draw();
	void Update();
	bool IsRunning();
	void Quit() { running = false; }

private:
	bool running;

	int mouseX, mouseY;
	RBSEngine* physicsEngine;
	list<Sprite> gameSprites;
	list<Frame>::iterator currentFrame;

	Material Material;
	SDL_Event* mainEvent;
	SDL_Window* Window;
	SDL_Renderer* Renderer;
	

};