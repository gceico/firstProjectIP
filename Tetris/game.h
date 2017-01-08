#ifndef _GAME_
#define _GAME_

#include "board.h"
#include "pieces.h"
#include "sdl.h"
#include <time.h>

#define WAIT_TIME 700

//Game
class Game
{
public:

	Game(Board *pBoard, Pieces *pPieces, SDL *pSDL, int pScreenHeight);

	void DrawScene ();
	void CreateNewPiece ();

	int mPosX, mPosY;
	int mPiece, mRotation;
	int mColor;


private:

	int mScreenHeight;
	int mNextPosX, mNextPosY;
	int mNextPiece, mNextRotation;
	
	Board *mBoard;
	Pieces *mPieces;
	SDL *mSDL;

	int GetRand (int pA, int pB);
	void InitGame();
	void DrawPiece (int pX, int pY, int pPiece, int pRotation, int pColor);
	void DrawBoard ();
};

#endif 
