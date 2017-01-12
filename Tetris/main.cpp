#include "game.h"
#include "iostream"
using namespace std;
SDL mSDL;
int mScreenHeight = mSDL.GetScreenHeight();

Pieces mPieces;

Board mBoard(&mPieces, mScreenHeight);

Game mGame(&mBoard, &mPieces, &mSDL, mScreenHeight);

unsigned long mTime1 = SDL_GetTicks();

void startGame() //Init Objects
{
	new(&mBoard) Board(&mPieces, mScreenHeight);
	new(&mGame)	 Game(&mBoard, &mPieces, &mSDL, mScreenHeight);

	mTime1 = SDL_GetTicks();
}

void checkInput (int mKey)
{
	switch (mKey)
	{
		case (SDLK_s) :
		{
						  mSDL.musicOnOff();
						  break;
		}
		case (SDLK_r) :
		{
						  mBoard.updateScore();
						  mBoard.updateFile();
						  mGame.mGameState = RESTART;
						  break;

		}
		case(SDLK_p) :
		{
						 mGame.mGameState = PLAY;
						 break;
		}
		case(SDLK_h) :
		{
						 mGame.mGameState = HELP;
						 break;
		}
		case(SDLK_l) :
		{
						 mGame.mGameState = LEADER;
						 break;
		}
		case(SDLK_m) :
		{
						 mGame.mGameState = MENU;
						 break;
		}
		case(SDLK_ESCAPE) :
		{
						mGame.mGameState = QUIT;
						break;
		}
		default :
		{
			break;
		}
	}
}

void RUN()
{
	startGame();

	if (Mix_PlayingMusic() == 0)
	{
		mSDL.musicOnOff();
	}

	if (Mix_PausedMusic())
	{
		Mix_PausedMusic();
	}

	else
	{
		Mix_ResumeMusic();
	}
	
	char finalScore[32];
	char highScore[32];
	int sprintInt;
	int xPosHS = 0;
	int yPosHS = 0;

	while (mGame.mGameState != QUIT)
	{   
		//RESTART STATE
		if (mGame.mGameState == RESTART)
		{   
			cout << "Enter restart state" << endl;
			RUN();
		}
		//OVER STATE
		if (mGame.mGameState == OVER)
		{   
			cout << "Enter over state" << endl;
			mSDL.DrawString(100, 0, "GAME OVER", mSDL.fontSpecial, mSDL.specialColor);
			mSDL.UpdateScreen();
			Mix_PauseMusic();
			mSDL.playEffect(mSDL.gameoverS);
			while (mGame.mGameState == OVER)
			{
				int mKey = mSDL.Pollkey();
				checkInput(mKey);
			}
		}
		//MENU STATE
		if (mGame.mGameState == MENU)
		{
			cout << "Enter menu state" << endl;
			mSDL.DrawMenu();
			while (mGame.mGameState == MENU)
			{
				int mKey = mSDL.Pollkey();
				checkInput(mKey);
			}
		}

		//HELP STATE
		if (mGame.mGameState == HELP)
		{
			cout << "Enter help state" << endl;
			mSDL.DrawHelp();
			while (mGame.mGameState == HELP)
			{
				int mKey = mSDL.Pollkey();
				checkInput(mKey);
			}
		}

		//LEADER STATE
		if (mGame.mGameState == LEADER)
		{
			cout << "Enter leader state" << endl;
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
				int mKey = mSDL.Pollkey();
				checkInput(mKey);
			}
		}

		//PLAY STATE
		if (mGame.mGameState == PLAY) 
		{
			cout << "Enter play state" << endl;
			while (mGame.mGameState == PLAY)
			{
				mSDL.ClearScreen();
				mGame.DrawScene();

				sprintInt = sprintf_s(finalScore, "%d", mBoard.finalScore);

				mSDL.DrawString(480, 115, "SCOR", mSDL.fontScor, mSDL.textColor);
				mSDL.DrawString(490, 155, finalScore, mSDL.fontScor, mSDL.textColor);
				mSDL.UpdateScreen();

				int mKey = mSDL.Pollkey();
				checkInput(mKey);
				switch (mKey)
				{

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

					if (mBoard.DeletePossibleLines() > 0)
					{
						mSDL.playEffect(mSDL.lineS);
					}

					if (mBoard.IsGameOver())
					{
						mGame.mGameState = OVER;

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

						if (mBoard.DeletePossibleLines() > 0)
						{
							mSDL.playEffect(mSDL.lineS);
						}

						if (mBoard.IsGameOver())
						{

							mGame.mGameState = OVER;
						}

						mGame.CreateNewPiece();
					}

					mTime1 = SDL_GetTicks();
				}
			}
		}
	}
}

int main()
{
	RUN();
	mBoard.updateScore();
	mBoard.updateFile();
	return 0;
}