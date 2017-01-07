#include "SDL.h"

static SDL_Surface *mScreen;
static Uint32 mColors [COLOR_MAX]= { 0x000000ff,0xff0000ff, 0x00ff00ff, 0x0000ffff,0x00ffffff, 0xff00ffff, 0xffff00ff,0xffffffff };

SDL::SDL() {
	InitGraph();
}

void SDL::ClearScreen() {
	boxColor(mScreen, 0, 0, mScreen->w - 1, mScreen->h - 1, mColors[BLACK]);
}

void SDL::DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC) {
	boxColor(mScreen, pX1, pY1, pX2, pY2 - 1, mColors[pC]);
}

int SDL::GetScreenHeight() {
	return mScreen->h;
}

void SDL::UpdateScreen() {
	SDL_Flip(mScreen);
}

int SDL::Pollkey() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			return event.key.keysym.sym;
		case SDL_QUIT:
			exit(3);
		}
	}
	return -1;
}

int SDL::Getkey() {
	SDL_Event event;
	while (true) {
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYDOWN)
			break;
		if (event.type == SDL_QUIT)
			exit(3);
	};
	return event.key.keysym.sym;
}

int SDL::IsKeyDown(int pKey) {
	Uint8* mKeytable;
	int mNumkeys;
	SDL_PumpEvents();
	mKeytable = SDL_GetKeyState(&mNumkeys);
	return mKeytable[pKey];
}

int SDL::InitGraph() {
	const SDL_VideoInfo *info;
	Uint8 video_bpp;
	Uint32 videoflags;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Couldn't initializate SDL: %s\n", SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);
	info = SDL_GetVideoInfo();
	if (info->vfmt->BitsPerPixel > 8) {
		video_bpp = info->vfmt->BitsPerPixel;
	}
	else {
		video_bpp = 16;
	}
	videoflags = SDL_SWSURFACE | SDL_DOUBLEBUF;
	if ((mScreen = SDL_SetVideoMode(640, 480, video_bpp, videoflags)) == NULL) {
		fprintf(stderr, "Couldn't set %ix%i video mode: %s\n", 640, 480, SDL_GetError());
		return 2;
	}
	return 0;
}