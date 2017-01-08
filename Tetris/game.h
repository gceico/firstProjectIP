#ifndef _GAME_
#define _GAME_

#include "Board.h"
#include "Pieces.h"
#include "SDL.h"
#include <time.h>

#define WAIT_TIME 700

//Game
class Game
{
public:

	Game(Board *pBoard, Pieces *pPieces, SDL *pSDL, int pScreenHeight);

	void DrawScene();
	void CreateNewPiece();

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

	int GetRand(int A, int B);
	void InitGame();
	void DrawPiece(int X, int Y, int Piece, int Rotation, int Color);
	void DrawBoard();
};

#endif 
