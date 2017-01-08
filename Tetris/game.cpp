#include "Game.h"
using namespace std;



//Init
Game::Game(Board *pBoard, Pieces *pPieces, SDL *pSDL, int pScreenHeight)
{
	mScreenHeight = pScreenHeight;

	mBoard = pBoard;
	mPieces = pPieces;
	mSDL = pSDL;

	InitGame();
}

int Game::GetRand(int A, int B)
{
	return rand() % (B - A + 1) + A;
}



//Init parameters
void Game::InitGame()
{

	srand((unsigned int)time(NULL));

	mColor = GetRand(2, 5);
	mPiece = GetRand(0, 6);
	mRotation = GetRand(0, 3);
	mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
	mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

	mColor = GetRand(2, 5);
	mNextPiece = GetRand(0, 6);
	mNextRotation = GetRand(0, 3);
	mNextPosX = BOARD_WIDTH + 5;
	mNextPosY = 5;
}



//Create a piece
void Game::CreateNewPiece()
{
	mColor = GetRand(2, 5);
	mPiece = mNextPiece;
	mRotation = mNextRotation;
	mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
	mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

	mNextPiece = GetRand(0, 6);
	mNextRotation = GetRand(0, 3);
}

//Draw piece
void Game::DrawPiece(int X, int Y, int Piece, int Rotation, int Color)
{
	color trueColor;

	int mPixelsX = mBoard->GetXPosInPixels(X);
	int mPixelsY = mBoard->GetYPosInPixels(Y);

	for (int i = 0; i < PIECE_BLOCKS; i++)
	{
		for (int j = 0; j < PIECE_BLOCKS; j++)
		{
			switch (mColor)
			{
			case 2: trueColor = RED;
				break;
			case 3: trueColor = GREEN;
				break;
			case 4: trueColor = BLUE;
				break;
			case 5: trueColor = YELLOW;
			}

			if (mPieces->GetBlockType(Piece, Rotation, j, i) != 0)
				mSDL->DrawRectangle(mPixelsX + i * BLOCK_SIZE,
				mPixelsY + j * BLOCK_SIZE,
				(mPixelsX + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
				(mPixelsY + j * BLOCK_SIZE) + BLOCK_SIZE - 1,
				trueColor);
		}
	}
}


//Draw board
void Game::DrawBoard()
{
	//Limits of the board in pixels	
	int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
	int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
	int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

	//Draw blocks
	mX1 += 1;
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			//filled or not
			if (!mBoard->IsFreeBlock(i, j))
				mSDL->DrawRectangle(mX1 + i * BLOCK_SIZE,
				mY + j * BLOCK_SIZE,
				(mX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
				(mY + j * BLOCK_SIZE) + BLOCK_SIZE - 1,
				DARKBLUE);
		}
	}
}


//Draw the scene
void Game::DrawScene()
{
	DrawBoard();
	DrawPiece(mPosX, mPosY, mPiece, mRotation, mColor);
	DrawPiece(mNextPosX, mNextPosY, mNextPiece, mNextRotation, mColor);
}
