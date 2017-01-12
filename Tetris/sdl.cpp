#include "sdl.h"
#include <string>
using namespace std;


static Uint32 mColors [COLOR_MAX] = {0x000000ff, 0xffffffff, 0xed2d0eff, 0x0fe00fff, 0x097bdcff, 0xd1d80fff, 0x090431ff};

//Aditional surfaces
SDL_Surface *background = NULL;

void SDL::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
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

void SDL::DrawString(int x, int y, char text[], TTF_Font *font, SDL_Color color)
{
	SDL_Surface *source = NULL;
	source = TTF_RenderText_Solid(font, text, color);
	if (source == NULL)
		return;

	apply_surface(x, y, source, mScreen);

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

//Menu
void SDL::DrawMenu()
{
	apply_surface(0, 0, menu, mScreen);
	UpdateScreen();
}

void SDL::DrawHelp()
{
	apply_surface(0, 0, help, mScreen);
	UpdateScreen();
}

void SDL::DrawLeaderBoard()
{
	apply_surface(0, 0, leaderBoard, mScreen);
	UpdateScreen();
}

//sounds
int SDL::playEffect(Mix_Chunk *effect)
{
	if (Mix_PlayChannel(-1, effect, 0) == -1)
	{
		return 1;
	}
	return 0;
}

int SDL::musicOnOff()
{
	if (Mix_PlayingMusic() == 0)
	{
		if (Mix_PlayMusic(music, -1) == -1)
		{
			return 1;
		}
	}
	else
	{
		if (Mix_PausedMusic() == 1)
		{
			Mix_ResumeMusic();
		}
		else
		{
			Mix_PauseMusic();
		}
	}
	return 0;
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

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		return 1;
	}

	SDL_WM_SetCaption("Tetris", NULL);
	
	if ((mScreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE)) == NULL)
	{
		return 2;
	}

	

	background = SDL_LoadBMP("Resources/background.bmp");
	menu = SDL_LoadBMP("Resources/menu.bmp");
	help = SDL_LoadBMP("Resources/help.bmp");
	leaderBoard = SDL_LoadBMP("Resources/leaderboard.bmp");
	//Sound init
	music = Mix_LoadMUS("SFX/music.wav");
	dropS = Mix_LoadWAV("SFX/drop.wav");
	lineS = Mix_LoadWAV("SFX/line.wav");
	gameoverS = Mix_LoadWAV("SFX/gameover.wav");
	gamestartS = Mix_LoadWAV("SFX/gamestart.wav");
	rotateS = Mix_LoadWAV("SFX/rotate.wav");
	moveS = Mix_LoadWAV("SFX/move.wav");

	//Font init
	fontTitle = TTF_OpenFont("Resources/textFont.ttf", 36);
	fontHScor = TTF_OpenFont("Resources/textFont.ttf", 40);
	fontScor = TTF_OpenFont("Resources/textFont.ttf", 42);
	fontSpecial = TTF_OpenFont("Resources/specialFont.ttf", 80);
	fontLeader = TTF_OpenFont("Resources/textFont.ttf",65);
	textColor = { 32, 32, 32 };
	specialColor = { 255, 255, 255 };

	if (background == NULL || menu == NULL || help == NULL || playAgain == NULL || exitGame == NULL)
		return 2;

	if (dropS == NULL || lineS == NULL || gameoverS == NULL || moveS == NULL ||
		gamestartS == NULL || rotateS == NULL || music == NULL)
		return 2;
	
	if (fontTitle == NULL || fontHScor == NULL || fontScor == NULL || fontSpecial == NULL || fontLeader == NULL)
		return 2;

	apply_surface(0, 0, background, mScreen);
    return 0;
}
