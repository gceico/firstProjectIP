#ifndef _PIECES_
#define _PIECES_

class Pieces
{
public:

	int GetBlockType(int positionPiece, int positionRotation, int positionX, int positionY);
	int GetXInitialPosition(int positionPiece, int positionRotation);
	int GetYInitialPosition(int positionPiece, int positionRotation);
};

#endif 
