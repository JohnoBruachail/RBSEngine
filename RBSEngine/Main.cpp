#include <iostream>

#include "Debug.h"
#include "SDLGameEngine.h"
using namespace std;

int main(int argc, char* argv[])
{	
	//initialises the game engine
	SDLGameEngine* game = new SDLGameEngine("TheGame", 50, 50, 1200, 800, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	while (game->IsRunning())
	{
		//main game loop
		game->HandleEvents();
		game->Update();
		game->Draw();
	}

	//deconstructor for game
	game->~SDLGameEngine();

	return 0;
}