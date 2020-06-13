#include "BasicHeader.h"
#include "GameScreen.h"
#include "Menu.h"

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