#ifndef _GAME_
#define _GAME_

#include "board.h"
#include "pieces.h"
#include "sdl.h"
#include <time.h>

#define WAIT_TIME 700
#define WAIT_FPS 50
enum gameState { MENU, PLAY, LEADER };
//Game
class Game
{
public:

	Game(Board *pBoard, Pieces *pPieces, SDL *pSDL, int pScreenHeight);

	void DrawScene ();
	void CreateNewPiece ();

	int mPosX, mPosY;
	int mPiece, mRotation;
	int mColor, mNextColor;
	int mGameState;

private:

	int mScreenHeight;
	int mNextPosX, mNextPosY;
	int mNextPiece, mNextRotation;
	void InitGame();
	Board *mBoard;
	Pieces *mPieces;
	SDL *mSDL;

	int GetRand (int pA, int pB);
	void DrawPiece (int pX, int pY, int pPiece, int pRotation, int pColor);
	void DrawBoard ();
};

#endif 
