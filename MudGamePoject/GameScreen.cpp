#include "BasicHeader.h"
#include "GameScreenHeader.h"

extern MCI_OPEN_PARMS m_mciOpenParms;
extern MCI_PLAY_PARMS m_mciPlayParms;
extern MCI_OPEN_PARMS mciOpen;
extern MCI_PLAY_PARMS mciPlay;
extern DWORD dwID;

// BGM, Sound Effect

void SetValue(int *nowScore, int *highestScore, int *saveScore, int *checkPlay, int *inputMode, bool *isPlay, bool *isHighScore, bool *isBlock)
{
	*nowScore = 0;
	*highestScore = 0;
	*saveScore = 0;
	//*checkPlay = 0;
	*inputMode = 0;

	*isPlay = TRUE;
	*isHighScore = TRUE;
	//*isBlock = FALSE;
}

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

void CheckBlockMode(int *inputMode, bool *isBlock, bool *isSoundEffect, int *checkPlay, int *blockCnt)
{
	if (*isSoundEffect) sndPlaySoundA(".\\sound\\highUp.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
	BYTE menuGap = 3;
	BYTE baseX = 14;
	BYTE baseY = 15;
	BYTE maxMenu = 3;
	BYTE menuString[3][20] = {
		" 1. Nomal Mode   ",
		" 2. Hard  Mode   ",
		" 3. Prev  Menu   ",
	};
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n");
	printf("          [ Choose Your Game Mode ]\n\n\n\n\n\n");
	printf("             [ 1. Nomal Mode   ]\n\n\n");
	printf("             [ 2. Hard  Mode   ]\n\n\n");
	printf("             [ 3. Prev  Menu   ]\n\n\n");

	*inputMode = SelectMenu(baseX, baseY, menuGap, maxMenu, menuString);
	
	if (*inputMode == inputNum_1)
	{
		if (*isSoundEffect) sndPlaySoundA(".\\sound\\highUp.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
		*checkPlay = gameScene;
		*isBlock = FALSE;
	}
	else if (*inputMode == inputNum_2)
	{
		system("cls");
		printf("\n\n\n\n\n\n");
		printf("       _   _    ___   ______  ______ \n");
		printf("      | | | |  / _ \\  | ___ \\ |  _  \\\n");
		printf("      | |_| | / /_\\ \\ | |_/ / | | | |\n");
		printf("      |  _  | |  _  | |    /  | | | |\n");
		printf("      | | | | | | | | | |\\ \\  | |/ / \n");
		printf("      |_| |_| |_| |_| |_| \\_| |___/  \n\n\n\n\n\n");
		printf("             [ 1. Block 1      ]\n\n\n");
		printf("             [ 2. Block 2      ]\n\n\n");
		printf("             [ 3. Prev  Menu   ]\n\n\n");
		maxMenu = 3;
		strcpy_s((char *)menuString[0], 18, " 1. Block 1      ");
		strcpy_s((char *)menuString[1], 18, " 2. Block 2      ");
		baseY = 17;
		*inputMode = SelectMenu(baseX, baseY, menuGap, maxMenu, menuString);
		if (*isSoundEffect) sndPlaySoundA(".\\sound\\highUp.wav", SND_ASYNC | SND_NODEFAULT);   // soundEffect
		*checkPlay = gameScene;
		*isBlock = TRUE;
		if (*inputMode == inputNum_1)
		{
			*blockCnt = 1;
		}
		else if (*inputMode == inputNum_2)
		{
			*blockCnt = 2;
		}
		else if (*inputMode == inputNum_3)
		{
			*checkPlay = gameSelectScene;
		}
	}
	
	else
	{
		if (*isSoundEffect) sndPlaySoundA(".\\sound\\highDown.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
		*checkPlay = mainScene;
	}
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

void CheckHighScore(int *nowScore, int *highestScore, int prevScore, int *saveScore, int *checkPlay, int sceneNum)
{
	*checkPlay = sceneNum;

	if (prevScore < *highestScore)
		*saveScore = -(*highestScore);	// 최댓값 갱신을 알리기 위한 음수화
	else
		*saveScore = *nowScore;
}

void CheckSaveHighScore(int *checkPlay, int *highestScore, int *saveScore)
{
	printf(">> ! WARNING !\n\n");
	printf(">> If You ReStart Game, \n   Your Score is Not Save!\n\n");
	printf(">> If You Want Save Score, Finish Game\n\n\n");
	printf("[ ReStart ]\n- Not Save Score, push '1'\n\n");
	printf("[ Finish Game ]\n- Save Score, push 'AnyKey'\n\nInput : ");

	int inputNum = 0;
	inputNum = _getch();

	if (inputNum == 224)	//  입력금지
	{
		while (inputNum == 224 || inputNum == 72 || inputNum == 75 || inputNum == 77 || inputNum == 80)
		{
			inputNum = _getch();
		}
	}
	
	if (inputNum == inputNum_1)
		*checkPlay = gameScene;
	else
	{
		*checkPlay = resultScene;
		*saveScore = -(*highestScore);	// 최댓값 갱신을 알리기 위한 음수화
	}
}

void SetNewNum(int(*mapArr)[BASICARRSIZE], int check)
{
	int posX = 0, posY = 0, randVal = 0;

	while (1)
	{
		check++;
		posX = rand() % BASICARRSIZE;
		posY = rand() % BASICARRSIZE;

		randVal = rand() % 2;
		if (randVal == 0)
			randVal = 2;
		else if (randVal == 1)
			randVal = 4;

		if (mapArr[posY][posX] != 0 && check >= 1)
		{
			check--;
			continue;
		}
		else if (mapArr[posY][posX] == 0 && check == 2)
		{
			mapArr[posY][posX] = randVal;
		}
		else
			mapArr[posY][posX] = randVal;

		if (check == 2)
			break;
	}
}

void SetBlock(int(*mapArr)[BASICARRSIZE], int blockCnt)
{
	int posX = 0, posY = 0, blockNum = 1, check = 0;

	while (1)
	{
		check++;
		posX = rand() % BASICARRSIZE;
		posY = rand() % BASICARRSIZE;

		if (mapArr[posY][posX] != 0 && check >= 1)
		{
			check--;
			continue;
		}
		else if (mapArr[posY][posX] == 0 && check == 2)
		{
			mapArr[posY][posX] = blockNum;
		}
		else
			mapArr[posY][posX] = blockNum;

		if (check == blockCnt)
			break;
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

// ※ : 리팩토링
void SetAbsVal_UpDown(int(*mapArr)[BASICARRSIZE], int posX)
{
	for (int i = 0; i < BASICARRSIZE; i++)
		mapArr[i][posX] = abs(mapArr[i][posX]);
}

void SetAbsVal_RightLeft(int(*mapArr)[BASICARRSIZE], int posY)
{
	for (int i = 0; i < BASICARRSIZE; i++)
		mapArr[posY][i] = abs(mapArr[posY][i]);
}

bool CheckGameContinue(int(*mapArr)[4], int *kbhitCnt, int *checkPlay, bool *isBgm, bool *isSoundEffect)
{
	// Continue : 1 / Restart & Revert : 2 / GameOver : AnyKey
	int inputNum = 0;
	inputNum = _getch();
	if (inputNum == 224)	//  입력금지
	{
		while (inputNum == 224 || inputNum == 72 || inputNum == 75 || inputNum == 77 || inputNum == 80)
		{
			inputNum = _getch();
		}
	}
	while (1)
	{
		if (inputNum == inputNum_1)
		{
			*checkPlay = inputNum_1;
			return TRUE;
		}
		else if (inputNum == inputNum_2)
		{
			*checkPlay = inputNum_2;
			return TRUE;
		}
		else if (inputNum == inputNum_3)
		{
			if (*isBgm)
			{
				*isBgm = FALSE;
				printf("[ BGM OFF ] ");
				mciSendCommandW(dwID, MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)&m_mciPlayParms);
			}
			else
			{
				*isBgm = TRUE;
				printf("[ BGM ON ] ");
				mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_mciPlayParms);
			}
		}
		else if (inputNum == inputNum_4)
		{
			if (*isSoundEffect)
			{
				*isSoundEffect = FALSE;
				printf("[ Sound Effect OFF ] ");
			}
			else
			{
				*isSoundEffect = TRUE;
				printf("[ Sound Effect ON ] ");
			}
		}
		else
			return FALSE;
		inputNum = _getch();
	}
}

// ------------------------------------------------------------------------------------------------------------

void CheckKbhitCnt(int *kbhitCnt)
{
	if (_kbhit())
		(*kbhitCnt)++;
}

void DeleteInput(int *kbhitCnt)
{
	int deleteInput = 0;
	rewind(stdin);

	while (*kbhitCnt>0)
	{
		deleteInput = _getch();
		while (1)
		{
			if (deleteInput == 224)
			{
				deleteInput = _getch();
				if (deleteInput == 72 || deleteInput == 75 || deleteInput == 77 || deleteInput == 80)
					break;
			}
			else
				break;
		}
		(*kbhitCnt)--;
	}
}

// ------------------------------------------------------------------------------------------------------------

void PrintArr(int(*mapArr)[BASICARRSIZE], char *string, int *kbhitCnt, int *nowScore, int *highestScore)
{
	int checkNum = 0;
	Sleep(200);
	system("cls");

	printf("\n\n     [ NOW_SCORE ]  2048  [ HIGHSCORE ]");
	printf("\n    [%12d ]      [%12d ]  \n\n\n", *nowScore, *highestScore);
	printf(" >> Now status '%s'\n\n", string);
	
	COORD pos;
	pos.X = 0;
	pos.Y = 8;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

	for (int i = 0; i < BASICARRSIZE; i++)
	{
		CheckKbhitCnt(kbhitCnt);
		DeleteInput(kbhitCnt);
		puts("    -------- -------- -------- -------- ");
		puts("   |        |        |        |        | ");
		for (int j = 0; j < BASICARRSIZE; j++)
		{
			checkNum = 0;
			while (pow(2, checkNum) != mapArr[i][j] && mapArr[i][j] != 0)
			{
				checkNum++;
			}
			if (j == 0)
				printf("   ");
			else
				printf("  ");
			TextColor(WHITE, BLACK);
			printf("|");
			TextColor(WHITE - checkNum, BLACK + checkNum);
			if (mapArr[i][j] > 1)
				printf("%6d", mapArr[i][j]);
			else if (mapArr[i][j] == 0)
				printf("      ");
			else if(mapArr[i][j] == 1)
			{
				TextColor(BLACK, WHITE);
				printf("     X");
			}
		}
		printf("  ");
		TextColor(WHITE, BLACK);
		puts("|\n   |        |        |        |        |");
	}
	puts("    -------- -------- -------- --------");
}

void PrintNewInput(int(*mapArr)[4], char *string, int *kbhitCnt, int *nowScore, int *highestScore)
{
	printf("%s", string);
	for (int i = 5; i > 0; i--)
	{
		CheckKbhitCnt(kbhitCnt);
		DeleteInput(kbhitCnt);
		Sleep(100);
		printf("%d ", i);
		CheckKbhitCnt(kbhitCnt);
		DeleteInput(kbhitCnt);
	}
	PrintArr(mapArr, "NewInput", kbhitCnt, nowScore, highestScore);
}

void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void ClearScreen_ReStart()
{
	COORD pos;
	pos.X = 0;
	pos.Y = 26;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

	for (int i = pos.Y; i < 46; i++)
	{
		printf("                                           \n");
	}

	pos.X = 0;
	pos.Y = 26;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}