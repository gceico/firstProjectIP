#include "Game.h"
#ifndef LINUX
#include <Windows.h>
#endif

#ifndef LINUX
int WINAPI WinMaine (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow)
#else
int main()
#endif
{
	SDL mSDL;
	int mScreenHeight = mSDL.GetScreenHeight();
	Pieces mPieces;
	Board mBoard(&mPieces, mScreenHeight);
	Game mGame(&mBoard, &mPieces, &mSDL, mScreenHeight);
	unsigned long mTime1 = SDL_GetTicks();
	while (!mSDL.IsKeyDown(SDLK_ESCAPE)) {
		mSDL.ClearScreen();
		mGame.DrawScene();
		mSDL.UpdateScreen();
		int mKey = mSDL.Pollkey();
		switch (mKey) {
		case (SDLK_RIGHT):
		{
			if (mBoard.IsPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
				mGame.mPosX++;
			break;
		}
		case (SDLK_LEFT):
		{
			if (mBoard.IsPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
				mGame.mPosX--;
			break;
		}
		case (SDLK_DOWN):
		{
			if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
				mGame.mPosY++;
			break;
		}
		case (SDLK_x):
		{
			while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation)) {
				mGame.mPosY++;
			}
			mBoard.StorePiece(mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRotation);
			mBoard.DeletePossibleLines();
			if (mBoard.IsGameOver()){
				mSDL.Getkey();
				exit(0);
			}
			mGame.CreateNewPiece();
			break;
		}
