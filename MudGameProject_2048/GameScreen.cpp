#include "BasicHeader.h"
#include "GameScreen.h"

int Start(int *highestScore, bool isBlock, int blockCnt)
{
	FILE *openFp = NULL;
	char fileName[128] = { 0 };

	if (isBlock)
	{
		if (blockCnt == 1)
			strcpy_s(fileName, "./HighestScore_Block1.dat");
		else
			strcpy_s(fileName, "./HighestScore_Block2.dat");
	}
	else
		strcpy_s(fileName, "./HighestScore_Basic.dat");

	if (_access(fileName, 00) == 0)	// 파일이 존재하는 경우
		fopen_s(&openFp, fileName, "rb");
	else
		fopen_s(&openFp, fileName, "wb");

	if (openFp == NULL)
	{
		puts("FileError!");
		exit(1);
		//return 0;
	}

	fread(highestScore, sizeof(int), 1, openFp);	// 바이너리 파일은 fread로 읽어야 함!
	fclose(openFp);
}

int Update(int *checkPlay, int *saveScore, int *nowScore, int *highestScore, int blockCnt, bool isBlock, bool *isBgm, bool *isSoundEffect)
{
	int inputNum = 0;
	int checkMaxNum = 0;
	int checkCanMove = 0;
	int checkGameOver = 0;
	int kbhitCnt = 0;

	int mapArr[BASICARRSIZE][BASICARRSIZE] = { 0 };
	int prevScore = *highestScore;

	SetNewNum(mapArr, 0);
	if (isBlock)
	{
		SetBlock(mapArr, blockCnt);	// 랜덤 장애물 설정
	}
	PrintArr(mapArr, "START", &kbhitCnt, nowScore, highestScore);
	// mapArr[1][1] = BASICARR_MAXNUM;	// Clear
	while (1)
	{
		PlayerInput(mapArr, &checkCanMove, &checkGameOver, &checkMaxNum, &kbhitCnt, nowScore, highestScore);

		if (checkCanMove == inputBtn_Esc)	// Pause
		{
			mciSendCommandW(dwID, MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)&m_mciPlayParms); // bgm pause
			if (*isSoundEffect) sndPlaySoundA(".\\sound\\highUp.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect

			printf(">> Pause\n\n[ OPTION ]\n- If You Continue Game, push '1'\n- ReStart Game, push '2'\n\n");
			printf("[ SOUND ]\n- BGM On/Off, push '3',\n- SoundeEffect On/Off, push '4'\n\n");
			printf("[ GAME OVER ]\n- Game Over, push 'AnyKey'\n\nInput : ");
			if (CheckGameContinue(mapArr, &kbhitCnt, checkPlay, isBgm, isSoundEffect))
			{
				if (*isBgm) mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_mciPlayParms);
				if (*isSoundEffect) sndPlaySoundA(".\\sound\\highDown.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect

				if (*checkPlay == inputNum_1)	// Continue
				{
					PrintNewInput(mapArr, "Continue\n\n>> Continue Game\n\nReady to Continue : ", &kbhitCnt, nowScore, highestScore);
					continue;
				}
				else // ReStart
				{
					if (prevScore < *highestScore)
					{
						ClearScreen_ReStart();
						CheckSaveHighScore(checkPlay, highestScore, saveScore);
					}
					else
						*checkPlay = gameScene;
				}
			}
			else
			{
				// ※ : 리팩토링
				if (*isBgm) mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_mciPlayParms);
				if (*isSoundEffect) sndPlaySoundA(".\\sound\\highDown.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect

				CheckHighScore(nowScore, highestScore, prevScore, saveScore, checkPlay, resultScene);
			}
			return 0;
		}

		if (checkCanMove == 0 && checkGameOver == BASICARRSIZE * BASICARRSIZE)	// GameOver
		{
			// Continue : 1 / Revert : 2 / GameOver : AnyKey
			mciSendCommandW(dwID, MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)&m_mciPlayParms); // bgm pause
			if (*isSoundEffect) sndPlaySoundA(".\\sound\\highUp.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect

			printf("\n>> GameOver\n\n[ OPTION ]\n- If You Revert Game, push '1'\n- ReStart Game, push '2'\n\n");
			printf("[ SOUND ]\n- BGM On/Off, push '3',\n- SoundeEffect On/Off, push '4'\n\n");
			printf("[ GAME OVER ]\n- Game Over, push 'AnyKey'\n\nInput : ");
			if (CheckGameContinue(mapArr, &kbhitCnt, checkPlay, isBgm, isSoundEffect))
			{
				if (*isBgm) mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_mciPlayParms);
				if (*isSoundEffect) sndPlaySoundA(".\\sound\\highDown.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect

				if (*checkPlay == inputNum_1)
				{
					PrintNewInput(mapArr, "Revert\n\n>> Revert Game\n\nReady to Revert : ", &kbhitCnt, nowScore, highestScore);
					continue;
				}
				else
				{
					if (prevScore < *highestScore)
					{
						ClearScreen_ReStart();
						CheckSaveHighScore(checkPlay, highestScore, saveScore);
					}
					else
						*checkPlay = gameScene;
				}
			}
			else
			{
				// ※ : 리팩토링
				if (*isBgm) mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_mciPlayParms);
				if (*isSoundEffect) sndPlaySoundA(".\\sound\\highDown.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect

				CheckHighScore(nowScore, highestScore, prevScore, saveScore, checkPlay, resultScene);
			}
			return 0;
		}

		if (checkMaxNum == BASICARR_MAXNUM)	// MaxNum in it
		{
			// Main : 1 / Restart : 2 / Exit : AnyKey
			mciSendCommandW(dwID, MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)&m_mciPlayParms); // bgm pause
			if (*isSoundEffect) sndPlaySoundA(".\\sound\\highUp.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect

			printf("\n>> Congratulations!\n>> You Made a MaxNumber!\n\n[ OPTION ]\n- Go to Main, push '1'\n- Start New Game, push '2'\n\n");
			printf("[ SOUND ]\n- BGM On/Off, push '3',\n- SoundeEffect On/Off, push '4'\n\n");
			printf("[ GAME OVER ]\n- Game Over, push 'AnyKey'\n\nInput : ");

			if (CheckGameContinue(mapArr, &kbhitCnt, checkPlay, isBgm, isSoundEffect))
			{
				if (*isBgm) mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_mciPlayParms);
				if (*isSoundEffect) sndPlaySoundA(".\\sound\\highDown.wav", SND_ASYNC | SND_NODEFAULT);

				// todo : 메인으로 돌아가기 전 최고점수 저장해야할듯
				if (*checkPlay == inputNum_1)
				{
					*checkPlay = mainScene;
				}
				else
					CheckHighScore(nowScore, highestScore, prevScore, saveScore, checkPlay, gameScene);
			}
			else
			{
				// ※ : 리팩토링
				if (*isBgm) mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_mciPlayParms);
				if (*isSoundEffect) sndPlaySoundA(".\\sound\\highDown.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect

				CheckHighScore(nowScore, highestScore, prevScore, saveScore, checkPlay, resultScene);
			}
			return 0;
		}

		if (checkCanMove != 0)	// Can Move
		{
			if(*isSoundEffect) sndPlaySoundA(".\\sound\\tone.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
			SetNewNum(mapArr, 1);
			PrintArr(mapArr, "NewBlock", &kbhitCnt, nowScore, highestScore);
		}
		else // Can't Move
		{
			if (*isSoundEffect) sndPlaySoundA(".\\sound\\twoTone.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
			PrintNewInput(mapArr, "\n>> Can't Move\n\nReady to New Input : ", &kbhitCnt, nowScore, highestScore);
			continue;
		}
	}
}

// ※ : 리팩토링
void PlayerInput(int(*mapArr)[BASICARRSIZE], int *checkCanMove, int *checkGameOver, int *checkMaxNum, int *kbhitCnt, int *nowScore, int *highestScore)
{
	*checkCanMove = 0;
	*checkGameOver = 0;
	*checkMaxNum = 0;

	int userInput = 0;

	CheckKbhitCnt(kbhitCnt);
	DeleteInput(kbhitCnt);

	printf("\nPush Your Button : ");
	userInput = _getch();

	if (userInput == 27)
	{
		puts("Esc\n");
		*checkCanMove = 27;
		return;
	}

	if (userInput == 224)
	{
		userInput = _getch();
		switch (userInput)
		{
		case 72:
			printf("Up Arrow");
			// ------------------------------------------------
			for (int i = 0; i < BASICARRSIZE; i++)
			{
				for (int j = 0; j < BASICARRSIZE - 1; j++)
				{
					if (IsCanMove(mapArr, j, i, checkCanMove, checkGameOver, checkMaxNum, plusPos, zeroPos))
						return;
				}
				if (mapArr[BASICARRSIZE - 1][i] != 0)	// 맨 마지막 값 저장
					(*checkGameOver)++;

				if (mapArr[BASICARRSIZE - 1][i] == BASICARR_MAXNUM)	// 최댓값 확인
					(*checkMaxNum) = BASICARR_MAXNUM;
			}
			// ------------------------------------------------
			for (int posX = 0; posX < BASICARRSIZE; posX++)
			{
				for (int posY = 0; posY < BASICARRSIZE; posY++)
				{
					if (posY == 0)
						continue;
					MoveToInput(mapArr, &posY, &posX, upMove, stayMove, zeroPos, minusPos, upDownPos, nowScore, highestScore);
				}
				SetAbsVal_UpDown(mapArr, posX);
			}
			PrintArr(mapArr, "Move to Up", kbhitCnt, nowScore, highestScore);
			break;

		case 80:
			printf("Down Arrow");
			// -------------------------------------------------------
			for (int i = 0; i < BASICARRSIZE; i++)
			{
				for (int j = BASICARRSIZE; j > 0; j--)
				{
					if (j == BASICARRSIZE)
						continue;

					if (IsCanMove(mapArr, j, i, checkCanMove, checkGameOver, checkMaxNum, minusPos, zeroPos))
						return;
				}
				if (mapArr[zeroPos][i] != 0)	// 맨 마지막 값 저장
					(*checkGameOver)++;

				if (mapArr[BASICARRSIZE - 1][i] == BASICARR_MAXNUM)	// 최댓값 확인
					(*checkMaxNum) = BASICARR_MAXNUM;
			}
			// ------------------------------------------------
			for (int posX = 0; posX < BASICARRSIZE; posX++)
			{
				for (int posY = BASICARRSIZE; posY >= 0; posY--)
				{
					if (posY >= BASICARRSIZE - downMove)
						continue;
					MoveToInput(mapArr, &posY, &posX, downMove, stayMove, arrSizePos, plusPos, upDownPos, nowScore, highestScore);
				}
				SetAbsVal_UpDown(mapArr, posX);
			}
			PrintArr(mapArr, "Move to Down", kbhitCnt, nowScore, highestScore);
			break;

		case 75:
			printf("Left Arrow");
			// -------------------------------------------------------
			for (int i = 0; i < BASICARRSIZE; i++)
			{
				for (int j = 0; j < BASICARRSIZE - 1; j++)
				{
					if (IsCanMove(mapArr, i, j, checkCanMove, checkGameOver, checkMaxNum, zeroPos, plusPos))
						return;
				}
				if (mapArr[i][BASICARRSIZE - 1] != 0)	// 맨 마지막 값 저장
					(*checkGameOver)++;

				if (mapArr[i][BASICARRSIZE - 1] == BASICARR_MAXNUM)	// 최댓값 확인
					(*checkMaxNum) = BASICARR_MAXNUM;
			}
			// ------------------------------------------------
			for (int posY = 0; posY < BASICARRSIZE; posY++)
			{
				for (int posX = 0; posX < BASICARRSIZE; posX++)
				{
					if (posX == 0)
						continue;
					MoveToInput(mapArr, &posY, &posX, stayMove, leftMove, zeroPos, minusPos, leftRightPos, nowScore, highestScore);
				}
				SetAbsVal_RightLeft(mapArr, posY);
			} // for()
			PrintArr(mapArr, "Move to Left", kbhitCnt, nowScore, highestScore);
			break;

		case 77:
			printf("Right Arrow");
			// ------------------------------------------------
			for (int i = 0; i < BASICARRSIZE; i++)
			{
				for (int j = BASICARRSIZE; j > 0; j--)
				{
					if (j == BASICARRSIZE)
						continue;

					if (IsCanMove(mapArr, i, j, checkCanMove, checkGameOver, checkMaxNum, zeroPos, minusPos))
						return;
				}
				if (mapArr[i][zeroPos] != 0)	// 맨 마지막 값 저장
					(*checkGameOver)++;

				if (mapArr[i][BASICARRSIZE - 1] == BASICARR_MAXNUM)	// 최댓값 확인
					(*checkMaxNum) = BASICARR_MAXNUM;
			}
			// ------------------------------------------------
			for (int posY = 0; posY < BASICARRSIZE; posY++)
			{
				for (int posX = BASICARRSIZE; posX >= 0; posX--)
				{
					if (posX >= BASICARRSIZE - rightMove)
						continue;
					MoveToInput(mapArr, &posY, &posX, stayMove, rightMove, arrSizePos, plusPos, leftRightPos, nowScore, highestScore);
				}
				SetAbsVal_RightLeft(mapArr, posY);
			} // for()
			PrintArr(mapArr, "Move to Right", kbhitCnt, nowScore, highestScore);
			break;

		default:
			break;
		}
	}
	else
	{
		printf("Wrong Btn\n");
	}
}

// ※ : 리팩토링
bool IsCanMove(int(*mapArr)[BASICARRSIZE], int posY, int posX, int *checkCanMove, int *checkGameOver, int *checkMaxNum, int moveY, int moveX)
{
	if (mapArr[posY][posX] == 0 && mapArr[posY + moveY][posX + moveX] > 1)
		(*checkCanMove)++;
	if (mapArr[posY][posX] == mapArr[posY + moveY][posX + moveX] && mapArr[posY][posX] > 1)
		(*checkCanMove)++;
	// 이동 가능 체크

	if (mapArr[posY][posX] != 0)
		(*checkGameOver)++;
	// 게임오버 체크
	// 마지막 위치의 값은 함수 밖에서 체크되고 있음에 유의
	// 후에 재작성 해볼것

	if (mapArr[posY][posX] == BASICARR_MAXNUM)
		(*checkMaxNum) = BASICARR_MAXNUM;

	if (checkCanMove == 0 && (*checkGameOver) == 16)
		return TRUE;
	if (checkCanMove == 0)
		return TRUE;

	return FALSE;
}

void MoveToInput(int(*mapArr)[BASICARRSIZE], int *posY, int *posX, int moveY, int moveX, int setStart, int setNext, int moveTo, int *nowScore, int *highestScore)
{
	if (mapArr[*posY][*posX] == 1)
		return;

	if (mapArr[*posY][*posX] != 0)	// 값이 있는 경우
	{
		if (mapArr[*posY + moveY][*posX + moveX] == 0)	// 앞 칸이 비었을 경우
		{
			mapArr[*posY + moveY][*posX + moveX] = mapArr[*posY][*posX];
			mapArr[*posY][*posX] = zeroPos;

			if (moveTo == upDownPos)
				*posY = setStart;
			else
				*posX = setStart;
		}
		else if (mapArr[*posY + moveY][*posX + moveX] == mapArr[*posY][*posX])	// 앞 칸의 숫자와 현재 칸의 숫자가 같을 경우
		{
			mapArr[*posY + moveY][*posX + moveX] = -(2 * mapArr[*posY][*posX]);
			mapArr[*posY][*posX] = zeroPos;

			*nowScore += abs(mapArr[*posY + moveY][*posX + moveX]);	// 중복 합침 막기위해 음수처리 해서 절대값화
			if (*nowScore > *highestScore)
			{
				*highestScore = *nowScore;
			}
		}
	}
}
