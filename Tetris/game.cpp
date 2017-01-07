#include "game.h"

Game::Game(Board *pBoard, Pieces *pPieces, SDL *pSDL, int pScreenHeight)
{
	mScreenHeight = pScreenHeight;
	mBoard = pBoard;
	mSDL = pSDL;

	InitGame();
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
	mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
	mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);


	mNextPiece = GetRand(0, 6);
	mNextRotation = GetRand(0, 3);
	mNextPosX = BOARD_WIDTH + 5;
	mNextPosY = 5;
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

void Game::DrawPiece(int X, int Y, int piece, int rotation)
{
	color mColor;
	int mPixelsX = mBoard->GetXPosInPixels(X);
	int mPixelsY = mBoard->GetYPosInPixels(Y);

	for (int i = 0; i < PIECE_BLOCKS; i++)
	{
		for (int j = 0; j < PIECE_BLOCKS; j++)
		{
			switch (mPieces->GetBlockType(piece, rotation, j, i))
			{
			case 1: mColor = GREEN;
				break;
			case 2: mColor = BLUE;
				break;
			}

			if (mPieces->GetBlockType(piece, rotation, j, i) != 0)
			{
				mSDL->DrawRectangle(mPixelsX + i * BLOCK_SIZE, mPixelsY + j * BLOCK_SIZE, (mPixelsX + i * BLOCK_SIZE) + BLOCK_SIZE - 1, (mPixelsY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, mColor);
			}
		}
	}
}

void Game::DrawBoard()
{
	int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
	int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
	int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

	mSDL->DrawRectangle(mX1 - BOARD_LINE_WIDTH, mY, mX1, mScreenHeight - 1, BLUE);
	mSDL->DrawRectangle(mX2, mY, mX2 + BOARD_LINE_WIDTH, mScreenHeight - 1, BLUE);

	mX1 += 1;
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			if (!mBoard->IsFreeBlock(i, j))
			{
				mSDL->DrawRectangle(mX1 + i * BLOCK_SIZE,mY + j * BLOCK_SIZE,(mX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1,(mY + j * BLOCK_SIZE) + BLOCK_SIZE - 1,		RED);
			}
		}
	}
}