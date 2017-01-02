#include "board.h"

Board::Board(Pieces *pices, int screenHeight)
{
	mScreenHeight = screenHeight;
	mPices = pPieces;
	initBoard();
}

void Board::InitBoard()
{
	int i, j;
	for (i = 0; i < BOARD_WIDTH; i++)
	{
		for (j = 0; j < BOARD_HEIGHT; j++)
			mBoard[i][j] = POS_FREE;
	}
}

void Board::StorePiece(int x, int y, int piece, rotation)
{
	int i1, i2, j1, j2;
	for (i1 = x, i2 = 0; i1 < x + PIECE_BLOCKS; i1++, i2++)
	{
		for (j1 = y, j2 = 0; j1 < y + PIECE_BLOCKS; j1++, j2++)
		{
			if (mPieces->GetBlockType(piece, rotaion, j2, i2) != 0)
				mBoard[i1][j1] = POS_FILLED;
		}
	}
}

bool Board::IsGameOver()
{
	int i;
	for (i = 0; i < BOARD_WIDTH; i++)
	{
		if (mBoard[i][0] == POS_FILLED)
			return true;
	}
	return false;
}

void Board : DeleteLine(int y)
{
	int i, j;
	for (j = y; j > 0; j--)
	{
		for (i = 0; i < BOARD_WIDTH; i++)
		{
			mBoard[i][j] = mBoard[i][j - 1];
		}
	}
}

void Board::DeletePossibleLines()
{
	int i, j;
	for (j = 0; j < BOARD_HEIGHT; j++)
	{
		i = 0;
		while (i < BOARD_WIDTH)
		{
			if (mBoard[i][j] != POS_FILLED)
				break;
			i++;
		}
		if (i == BOARD_WIDTH)
			DeleteLine(j);
	}
}

bool Board::IsFreeBlock(int x, int y)
{
	if (mBoard[x][y] == PO)
}

int Board::GetXPosInPixels(int pos)
{
	return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (pos * BLOCK_SIZE));
}

int Board::GetYPozInPixels(int pos)
{
	return ((mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pos * BLOCK_SIZE);
}

bool Board::IsPossibleMovement(int x, int y, int piece, int rotation)
{
	int i1, i2, j1, j2;
	for (i1 = x, i2 = 0; i1 < x + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = y, j2 = 0; j1 < y + PUECE_BLOCKS; j1++, j2++)
		{
			if (i1 < 0 || i1 > BOARD_WIDTH - 1 || j1 > BOARD_HEIGHT - 1)
			{
				if (mPices->GetBlockType(piece, rotation, j2, i2) != 0)
					return 0;
			}

			if (j1 >= 0)
			{
				if ((mPices->GetBlockType(piece, rotation, j2, i2) != 0) && (!IsFreeBlock(i1, j1)))
					return false;
			}
		}
	}
	return true;
}