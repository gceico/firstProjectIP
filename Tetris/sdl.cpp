#include "sdl.h"
#include <string>
using namespace std;

static SDL_Surface *mScreen;
static Uint32 mColors [COLOR_MAX] = {0x000000ff, 0xffffffff, 0xed2d0eff, 0x0fe00fff, 0x097bdcff, 0xd1d80fff, 0x090431ff};

//Aditional surfaces
SDL_Surface *background = NULL;
SDL_Surface *scoreS = NULL;
SDL_Surface	*highScoreS = NULL;

//Font
TTF_Font *font = NULL;
SDL_Color textColor = {0, 0, 0};

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, NULL, destination, &offset);
}

//init
SDL::SDL() 
{
	InitGraph ();
}

							
//Clear the screen
void SDL::ClearScreen() 
{
	apply_surface(0, 0, background, mScreen);
}

								
//Draw a rectangle of a given color
void SDL::DrawRectangle (int pX1, int pY1, int pX2, int pY2, enum color pC)
{
	boxColor (mScreen, pX1, pY1, pX2, pY2-1, mColors[pC]);
}
								
//Return the screen height
int SDL::GetScreenHeight()
{
	return mScreen->h;
}


								
//Update screen
void SDL::UpdateScreen()
{
	SDL_Flip(mScreen);
}


							
//Keyboard Input
int SDL::Pollkey()
{
	SDL_Event event;
	while ( SDL_PollEvent(&event) ) 
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:
				return event.key.keysym.sym;
			case SDL_QUIT:
				exit(3);
		}
	}
	return -1;
}

int SDL::Getkey()
{
	SDL_Event event;
	while (true)
	{
	  SDL_WaitEvent(&event);
	  if (event.type == SDL_KEYDOWN)
		  break;
      if (event.type == SDL_QUIT)
		  exit(3);
	};
	return event.key.keysym.sym;
}

int SDL::IsKeyDown (int pKey)
{
	Uint8* mKeytable;
	int mNumkeys;
	SDL_PumpEvents();
	mKeytable = SDL_GetKeyState(&mNumkeys);
	return mKeytable[pKey];
}

								
//SDL Graphical Initialization
int SDL::InitGraph()
{    
	if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
	{
		return 1;
	}

	if (TTF_Init() < 0)
	{
		return 1;
	}

	SDL_WM_SetCaption("Tetris", NULL);
	
	if ((mScreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE)) == NULL)
	{
		return 2;
	}

	background = SDL_LoadBMP("Resources/background.bmp");

	if (background == NULL)
		return 2;
	else
		apply_surface(0, 0, background, mScreen);

	font = TTF_OpenFont("Resources/font.ttf", 3);
	if (font == NULL)
	{
		return 2;
	}

	scoreS = TTF_RenderText_Solid(font, "ACEST FONT", textColor);

	if (scoreS == NULL)
		return 2;
	else
		apply_surface(0, 0, scoreS, mScreen);

    return 0;
}
