#include "game.h"
using namespace std;
SDL mSDL;
int mScreenHeight = mSDL.GetScreenHeight();

Pieces mPieces;

Board mBoard(&mPieces, mScreenHeight);

Game mGame(&mBoard, &mPieces, &mSDL, mScreenHeight);

unsigned long mTime1 = SDL_GetTicks();
unsigned long mTime3 = 0;

void startGame() //Init Objects
{

	new(&mSDL) SDL();
	int mScreenHeight = mSDL.GetScreenHeight();

	new(&mBoard) Board(&mPieces, mScreenHeight);
	new(&mGame)	 Game(&mBoard, &mPieces, &mSDL, mScreenHeight);

	unsigned long mTime1 = SDL_GetTicks();
	unsigned long mTime3 = 0;
}

void RUN()
{
	startGame();
	mSDL.musicOnOff();
	char finalScore[32];
	char highScore[32];
	int sprintInt;
	int xPosHS = 0;
	int yPosHS = 0;

	while (!mSDL.IsKeyDown(SDLK_ESCAPE))
	{
		//MENU STATE
		if (mGame.mGameState == MENU)
		{
			mSDL.DrawMenu();
			while (mGame.mGameState == MENU)
			{
				int mKeyMenu = mSDL.Pollkey();
				switch (mKeyMenu)
				{
				case (SDLK_s) :
				{
								  mSDL.musicOnOff();
								  break;
				}
				case (SDLK_r) :
				{
								  RUN();
								  break;
				}
				case(SDLK_p) :
				{
								 mGame.mGameState = PLAY;
								 break;
				}
				case(SDLK_l) :
				{
								 mGame.mGameState = LEADER;
								 break;
				}
				case(SDLK_ESCAPE) :
				{
								exit(0);
								break;
				}
				}
			}
		}

		//LEADER STATE
		if (mGame.mGameState == LEADER)
		{
			mSDL.DrawLeaderBoard();
			yPosHS = 140;
			for (int i = 0; i < TOP_SCORES; i++)
			{
				int sprintInt = sprintf_s(highScore, "%d", mBoard.highScore[i]);
				mSDL.DrawString(352, yPosHS, highScore, mSDL.fontLeader, mSDL.textColor);
				if (i < TOP_SCORES - 1)
					yPosHS += 60;
				else
					yPosHS = 140;

			}
			mSDL.UpdateScreen();
			while (mGame.mGameState == LEADER)
			{
				int mKeyLeader = mSDL.Pollkey();
				switch (mKeyLeader)
				{
				case (SDLK_s) :
				{
								  mSDL.musicOnOff();
								  break;
				}
				case(SDLK_p) :
				{
								 mGame.mGameState = PLAY;
								 break;
				}
				case(SDLK_m) :
				{
								 mGame.mGameState = MENU;
								 break;
				}
				case(SDLK_ESCAPE) :
				{
								exit(0);
								break;
				}
				}
			}
		}

		//PLAY STATE
		while (mGame.mGameState == PLAY)
		{
			mSDL.ClearScreen();
			mGame.DrawScene();

			sprintInt = sprintf_s(finalScore, "%d", mBoard.finalScore);
			for (int i = 0; i < TOP_SCORES; i++)
			{
				mSDL.DrawString(77, 125, "TOP 5", mSDL.fontTitle, mSDL.textColor);
				sprintInt = sprintf_s(highScore, "%d", mBoard.highScore[i]);
				mSDL.DrawString(90, yPosHS, highScore, mSDL.fontHScor, mSDL.textColor);
				if (i < TOP_SCORES - 1)
					yPosHS += 30;
				else
					yPosHS = 160;

			}

			mSDL.DrawString(480, 115, "SCOR", mSDL.fontScor, mSDL.textColor);
			mSDL.DrawString(490, 155, finalScore, mSDL.fontScor, mSDL.textColor);
			mSDL.UpdateScreen();

			int mKey = mSDL.Pollkey();

			switch (mKey)
			{
				case (SDLK_s):
				{
					mSDL.musicOnOff();
					break;
				}
				case (SDLK_m):
				{
					mGame.mGameState = MENU;
					break;
				}
				case (SDLK_RIGHT):
				{
					if (mBoard.IsPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
					{
						mGame.mPosX++;
						mSDL.playEffect(mSDL.moveS);
					}
					break;
				}
				case (SDLK_LEFT):
				{
					if (mBoard.IsPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
					{
						mGame.mPosX--;
						mSDL.playEffect(mSDL.moveS);
					}
					break;
				}
				case (SDLK_DOWN):
				{
					if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
					{
						mGame.mPosY++;
						mSDL.playEffect(mSDL.moveS);
					}
					break;
				}
				case (SDLK_x):
				{
					mSDL.playEffect(mSDL.dropS);
					// Check collision from up to down
					while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation))
					{
						mGame.mPosY++;
					}

					mBoard.StorePiece(mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRotation);

					if (mBoard.DeletePossibleLines())
					{
						mSDL.playEffect(mSDL.lineS);
					}

					if (mBoard.IsGameOver())
					{
						mTime3 = SDL_GetTicks();
						mSDL.DrawString(100, 0, "GAME OVER", mSDL.fontSpecial, mSDL.specialColor);
						mSDL.UpdateScreen();
						mSDL.musicOnOff();
						mSDL.playEffect(mSDL.gameoverS);

						while (!mSDL.IsKeyDown(SDLK_ESCAPE))
						{
							int mKeyOver = mSDL.Pollkey();
							switch (mKeyOver)
							{
							case(SDLK_r):
							{
								RUN();
								break;
							}
							}
						}
						mSDL.Getkey();
						exit(0);
					}

					mGame.CreateNewPiece();
					break;
				}

				case (SDLK_z):
				{
					if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation + 1) % 4))
					{
						mSDL.playEffect(mSDL.rotateS);
						mGame.mRotation = (mGame.mRotation + 1) % 4;
					}
					break;
				}
				case(SDLK_ESCAPE) :
				{
					mBoard.updateScore();
					mBoard.updateFile();
					exit(0);
					break;
				}
			}

			//Vertical movement
			unsigned long mTime2 = SDL_GetTicks();

			while ((mTime2 - mTime1) < WAIT_FPS)
			{
				mTime2 = SDL_GetTicks();
			}
			

			if ((mTime2 - mTime1) > WAIT_TIME)
			{
				if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
				{
					mGame.mPosY++;
				}
				else
				{
					mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);

					if (mBoard.DeletePossibleLines())
					{
						mSDL.playEffect(mSDL.lineS);
					}

					if (mBoard.IsGameOver())
					{

						mSDL.musicOnOff();
						mSDL.playEffect(mSDL.gameoverS);
						mTime3 = SDL_GetTicks();
						mSDL.DrawString(110, 0, "GAME OVER", mSDL.fontSpecial, mSDL.specialColor);
						mSDL.UpdateScreen();

						while (!mSDL.IsKeyDown(SDLK_ESCAPE))
						{
							int mKeyOver = mSDL.Pollkey();
							switch (mKeyOver)
							{
							case(SDLK_r):
							{
								RUN();
								break;
							}
							}
						}
						mSDL.Getkey();
						exit(0);
					}

					mGame.CreateNewPiece();
				}

				mTime1 = SDL_GetTicks();
			}
		}
	}
}

int main()
{
	RUN();
	return 0;
}