#include "game.h"

Game::Game(Board *pBoard, Pieces *pPieces, SDL *pSDL, int pScreenHeight)
{
	mScreenHeight = pScreenHeight;
	mBoard = pBoard;
	mSDL = pSDL;

	initGame();
}

int Game::GetRand(int A, int B)
{
	return rand() % (B - A + 1) + A;
}

void Game::InitGame()
{
	srand((unsigned int)time(NULL));

	mPiece = GetRand(0, 6);
	mRotation = GetRand(0, 3);
	mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation;
	mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);


	mNextPiece = GetRand(0, 6);
	mNextRotation = GetRand(0, 3);
	mNextPosY = BOARD_WIDTH + 5;
	mNextPosy = 5;
}

void Game::CreateNewPiece()
{
	mPiece = mNextPiece;
	mRotation = mNextRotation;
	mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
	mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

	mNextPiece = GetRand(0, 6);
	mNextRotation = GetRand(0, 3);
}



