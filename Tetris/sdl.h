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
	void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);

	SDL_Surface *mScreen;
	SDL_Surface *background;
	SDL_Surface *menu;
	SDL_Surface *leaderBoard;
	SDL_Surface	*help;

	void DrawMenu();
	void DrawHelp();
	void DrawLeaderBoard();

	TTF_Font *fontTitle;
	TTF_Font *fontHScor;
	TTF_Font *fontScor;
	TTF_Font *fontLeader;
	TTF_Font *fontSpecial;
	SDL_Color textColor;
	SDL_Color specialColor;

	Mix_Music *music = NULL;
	Mix_Chunk *rotateS = NULL;
	Mix_Chunk *dropS = NULL;
	Mix_Chunk *moveS = NULL;
	Mix_Chunk *lineS = NULL;
	Mix_Chunk *gameoverS = NULL;
	Mix_Chunk *gamestartS = NULL;
	int playEffect(Mix_Chunk *effect);
	int musicOnOff();
};

#endif