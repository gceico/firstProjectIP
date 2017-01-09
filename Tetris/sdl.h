//main library
#include "SDL/include/SDL.h"	
#pragma comment (lib, "SDL/lib/SDL.lib")

//fill boxes
#include "SDL/include/SDL_gfxPrimitives.h" 
#pragma comment (lib, "SDL/lib/SDL_GfxPrimitives_Static.lib") 

//fonts
#include "SDL/include/SDL_ttf.h"
#pragma comment (lib, "SDL/lib/SDL_ttf.lib")

//sounds
#include "SDL/include/SDL_mixer.h"
#pragma comment (lib, "SDL/lib/SDL_mixer")

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 16;
enum color {BLACK, WHITE, RED, GREEN, BLUE, YELLOW, DARKBLUE, COLOR_MAX};

#ifndef _SDL_
#define _SDL_

class SDL
{
public:

	SDL						();
	void DrawString			(int x, int y, char text[], TTF_Font *font, SDL_Color color);
	void DrawRectangle		(int pX1, int pY1, int pX2, int pY2, enum color pC);
	void ClearScreen		();
	int GetScreenHeight		();
	int InitGraph			();
	int Pollkey				();
	int Getkey				();
	int IsKeyDown			(int pKey);
	void UpdateScreen		();

	SDL_Surface *mScreen;
	TTF_Font *fontTitle;
	TTF_Font *fontHScor;
	TTF_Font *fontScor;
	TTF_Font *fontSpecial;
	SDL_Color textColor;
	SDL_Color specialColor;
};

#endif