#include "SDLGameEngine.h"

SDLGameEngine::~SDLGameEngine(void)
{
}

//constructor, running needs to be true
//initializing game and inputing window sizes for sdl window 
SDLGameEngine::SDLGameEngine(const char* title, int xpos, int ypos, int width, int height, int flags) : running(true)
{
	DEBUG_MSG("Constructing Game");
	SDL_Init(SDL_INIT_EVERYTHING);

	Window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	
	SDL_SetRenderDrawColor(Renderer, 200, 200, 200, 255);
	//load physics engine here
	physicsEngine = new RBSEngine();

	Sprite newSprite(physicsEngine, 100, 100, 0, 0, 200, 700, Material, 0);
	gameSprites.push_back(newSprite);

	Sprite newSprite1(physicsEngine, 100, 100, 0, 0, 200, 500, Material, 1);
	gameSprites.push_back(newSprite1);

	Sprite newSprite2(physicsEngine, 300, 100, 0, 0, 700, 700, Material, 0);
	gameSprites.push_back(newSprite2);

	Sprite newSprite4(physicsEngine, 100, 100, 0, 0, 700, 500, Material, 12);
	gameSprites.push_back(newSprite4);
}
/*
SDLGameEngine::~SDLGameEngine()
{
	DEBUG_MSG("Deconstructing Renderer");
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
	SDL_Quit();
}
*/

void SDLGameEngine::HandleEvents() 
{
	// look at the states in textbasedshwdowrun
	//on keypress I want to create a new object, circle

	SDL_Event mainEvent;
	while (SDL_PollEvent(&mainEvent))
		{
			switch(mainEvent.type)
			case SDL_MOUSEBUTTONDOWN :
				switch(mainEvent.button.button)
				{
				case SDL_BUTTON_LEFT:
					DEBUG_MSG("Left Mouse Button Pressed");
					
					SDL_GetMouseState(&mouseX, &mouseY);
					
					//could just make a rect here and work with that instead.

					Sprite newSprite(physicsEngine, mouseX+100, mouseY+100, mouseX, mouseY, mouseX, mouseY, Material, 4);
					gameSprites.push_back(newSprite);

					break;
				//default:
					//SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
					break;
				}
				switch(mainEvent.key.keysym.sym)
				{
				case SDL_KEYDOWN:
					case SDLK_UP:
						DEBUG_MSG("Up Key Pressed");					
						currentFrame = physicsEngine->frameList.end();
						currentFrame--;
						currentFrame->velocity.y = -0.05;
						//currentFrame->velocity.x = 0;

						break;
					case SDLK_DOWN:
						DEBUG_MSG("Down Key Pressed");
						currentFrame = physicsEngine->frameList.end();
						currentFrame--;
						currentFrame->velocity.y = +0.05;
						//currentFrame->velocity.x = 0;

						break;
					case SDLK_LEFT:
						DEBUG_MSG("Left Key Pressed");
						currentFrame = physicsEngine->frameList.end();
						currentFrame--;
						currentFrame->velocity.x = -0.05;
						//currentFrame->velocity.y = 0;
					
						break;
					case SDLK_RIGHT:
						DEBUG_MSG("Right Key Pressed");
						currentFrame = physicsEngine->frameList.end();
						currentFrame--;
						currentFrame->velocity.x = 0.05;
						//currentFrame->velocity.y = 0;
									
						break;
					case SDLK_SPACE:
						DEBUG_MSG("Right Key Pressed");
						currentFrame = physicsEngine->frameList.end();
						currentFrame--;
						currentFrame->velocity.x = 0;
						currentFrame->velocity.y = 0;
									
						break;
				}
		}
}

void SDLGameEngine::Update() 
{
	//physics engine update here
	physicsEngine->Update();
	
	if(physicsEngine->frameList.empty() == false){

		list<Frame>::iterator fit = physicsEngine->frameList.begin();
		for(list<Sprite>::iterator sit = gameSprites.begin(); sit != gameSprites.end(); sit++){
			
			if(sit->fixed != true){
				sit->sprite.x = fit->position.x - sit->sprite.w / 2;
				sit->sprite.y = fit->position.y - sit->sprite.h / 2; 
			}
			else{

			}
			fit++;
		}
	}

}

void SDLGameEngine::Draw() 
{
	SDL_RenderClear(Renderer);
	
	// draw everyhting in the scene here.
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	for(list<Sprite>::iterator it = gameSprites.begin(); it != gameSprites.end(); it++){
		SDL_RenderDrawRect(Renderer, &it->sprite);
	}
	SDL_SetRenderDrawColor(Renderer, 200, 200, 200, 255);
	SDL_RenderPresent(Renderer);
}

bool SDLGameEngine::IsRunning()
{
	return running;
}