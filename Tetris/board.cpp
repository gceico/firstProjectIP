#include "board.h"
using namespace std;

//Score
void Board::readScore()
{
	ifstream fin("Resources/score.txt");
	int i;
	for (i = 0; i < TOP_SCORES; i++)
		fin >> highScore[i];
	fin.close();
}

void Board::updateScore()
{
	int i, j, auxA, auxB;
	for (i = 0; i < TOP_SCORES; i++)
	{
		if (finalScore >= highScore[i])
		{
			auxA = highScore[i];
			highScore[i] = finalScore;
			for (j = i + 1; j < TOP_SCORES; j++)
			{
				auxB = highScore[j];
				highScore[j] = auxA;
				auxA = auxB;
			}
			return;
		}
	}
}

void Board::updateFile()
{
	int i;
	ifstream fin("Resources/score.txt");
	fin.close();

	ofstream ofs("Resources/score.txt", ios::out | ios::trunc); //Delete file data
	for (i = 0; i < TOP_SCORES; i++)
		ofs << highScore[i] << endl;
}

//Init
Board::Board (Pieces *pPieces, int pScreenHeight)
{
	mScreenHeight = pScreenHeight;

	mPieces = pPieces;
	readScore();
	InitBoard();
}

void Board::InitBoard()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
		for (int j = 0; j < BOARD_HEIGHT; j++)
			mBoard[i][j] = POS_FREE;
}
								
//Store a piece in the board by filling the blocks
void Board::StorePiece (int pX, int pY, int pPiece, int pRotation)
{
	finalScore += 1;

	for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
		{	
			if (mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0)		
				mBoard[i1][j1] = POS_FILLED;	
		}
	}
}

//Game over
bool Board::IsGameOver()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		if (mBoard[i][0] == POS_FILLED)
		{
			updateScore();
			updateFile();
			return true;
		}
	}
	return false;
}

//Delete line
void Board::DeleteLine (int pY)
{
	finalScore += 10;

	for (int j = pY; j > 0; j--)
	{
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			mBoard[i][j] = mBoard[i][j-1];
		}
	}

}
						
//Delete more lines
bool Board::DeletePossibleLines ()
{
	bool wasDeleted = false;
	for (int j = 0; j < BOARD_HEIGHT; j++)
	{
		int i = 0;
		while (i < BOARD_WIDTH)
		{
			if (mBoard[i][j] != POS_FILLED) break;
			i++;
		}

		if (i == BOARD_WIDTH)
		{
			DeleteLine(j);
			wasDeleted = true;
		}
	}
	return wasDeleted;
}


bool Board::IsFreeBlock (int pX, int pY)
{
	if (mBoard [pX][pY] == POS_FREE) 
		return true;
	else 
		return false;
}
								

int Board::GetXPosInPixels (int pPos)
{
	return  ( ( BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) ) + (pPos * BLOCK_SIZE) );
}

//In pixels
int Board::GetYPosInPixels (int pPos)
{
	return ( (mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pPos * BLOCK_SIZE) );
}

//check if is possible
bool Board::IsPossibleMovement (int pX, int pY, int pPiece, int pRotation)
{
	for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
		{	
			if (i1 < 0 || i1 > BOARD_WIDTH  - 1	|| j1 > BOARD_HEIGHT - 1) //outside the limits
			{
				if (mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0)
					return 0;		
			}

			//Colision with stored blocks
			if (j1 >= 0)	
			{
				if ((mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0) && (!IsFreeBlock (i1, j1))	)
					return false;
			}
		}
	}

	return true;
}
