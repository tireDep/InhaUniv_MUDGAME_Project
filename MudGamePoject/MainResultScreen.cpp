#include "BasicHeader.h"
#include "MainResultHeader.h"

extern MCI_OPEN_PARMS m_mciOpenParms;
extern MCI_PLAY_PARMS m_mciPlayParms;
extern DWORD m_dwDeviceID;
extern MCI_OPEN_PARMS mciOpen;
extern MCI_PLAY_PARMS mciPlay;

extern int dwID;
// BGM, Sound Effect

void MainScreen(int *checkPlay, bool *isBgm, bool *isSoundEffect)
{
	int inputNum = 0;
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n");
	printf("         ___     ___     ___     ___  \n");
	printf("       || 2 |  || 0 |  || 4 |  || 8 | \n");
	printf("       ||___|  ||___|  ||___|  ||___| \n");
	printf("       |/___|  |/___|  |/___|  |/___| \n");
	printf("\n\n\n\n\n\n\n");

	printf("             [ 1. Game Start ]\n\n\n");
	printf("             [ 2. Tutorial  ]\n\n\n");
	printf("            [ 3. Sound Option ]\n\n\n\n\n\n");

	printf("         Press Another Key is Exit...\n\n");

	inputNum = _getch();

	if (*isSoundEffect) sndPlaySoundA(".\\sound\\highUp.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
	if (inputNum == inputNum_1)
		*checkPlay = gameScene;	// ���ӽ��� ���ý�

	else if (inputNum == inputNum_2)
		TutorialScreen(checkPlay, inputNum, isSoundEffect);

	else if (inputNum == inputNum_3)
		SoundOption(isBgm, isSoundEffect, checkPlay);

	else
	{
		if (*isSoundEffect) sndPlaySoundA(".\\sound\\highDown.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
		*checkPlay = gameExit;
	}
		
}

void TutorialScreen(int *checkPlay, int inputNum, bool *isSoundEffect)
{
	if (*isSoundEffect) sndPlaySoundA(".\\sound\\highUp.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
	system("cls");
	printf("\n\n                 [ TUTORIAL ]\n\n\n");

	printf(">> ���Ӽ���\n\n");
	printf("- ���� ���ں���� ����\n  ū ���ڸ� ����� ����\n\n\n");

	printf(">> ���ӹ��\n\n");
	printf("- ����Ű��             ���� \n");
	printf("  ���ں����           ���� \n");
	printf("  �̵���ų �� ����     ���� \n");

	printf("\n- ���� ���ں���� ���� ���,\n  �������鼭 ������ ���� �� ����\n");
	printf("\n  �� : ��2��2 => ���2+2 => ����4\n\n\n");

	printf(">> �Է�Ű\n\n- �̵� : ��, ��, ��, ��\n\n- �Ͻ����� : ESC\n\n\n");
	printf(">> ���ӿ���\n\n- ��� ĭ�� ���� ����� �ְ�,\n  �ش� �������� �̵��� �� ���� ��\n\n\n");
	printf("    [ Input AnyKey, You Can Go To Main ]\n");

	inputNum = _getch();
	if (inputNum != NULL)
		*checkPlay = mainScene;

	if (*isSoundEffect) sndPlaySoundA(".\\sound\\highDown.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
}

void SoundOption(bool *isBgm, bool *isSoundEffect, int *checkPlay)
{
	if (*isSoundEffect) sndPlaySoundA(".\\sound\\highUp.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
	int inputNum = 0;
	while (1)
	{
		Sleep(250);
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("              [ Sound Option ]\n\n\n\n");
		printf("    >> Bgm On / Off, push '1'\n\n\n");
		printf("    >> SoundEffect On / Off, push '2'\n\n\n");
		printf("    >> Go to Main, push 'AnyKey'\n\n");

		inputNum = _getch();
		if (inputNum == inputNum_1)
		{
			if (*isBgm)
			{
				printf("\n\n                 [ BGM OFF ]\n\n");
				mciSendCommandW(dwID, MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)&m_mciPlayParms);
				*isBgm = FALSE;
			}
			else
			{
				printf("\n\n                 [ BGM ON ]\n\n");
				mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_mciPlayParms);
				*isBgm = TRUE;
			}
		}
		else if (inputNum == inputNum_2)
		{
			if (*isSoundEffect)
			{
				printf("\n\n           [ Sound Effect OFF ]\n\n");
				*isSoundEffect = FALSE;
			}
			else
			{
				printf("\n\n           [ Sound Effect ON ]\n\n");
				*isSoundEffect = TRUE;
			}
		}
		else
		{
			if (*isSoundEffect) sndPlaySoundA(".\\sound\\highDown.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
			*checkPlay = mainScene;
			return;
		}
	}
}

// ------------------------------------------------------------------------------------------------------------

bool ResultScreen(bool *isHighScore, bool *isPlay, int *saveScore, int *checkPlay, bool isBlock, bool isSoundEffect, int blockCnt)
{
	FILE *openFp = NULL;
	int inputNum = 0;
	char fileName[128] = { 0 };

	printf("AnyKey\n\n");
	Sleep(200);
	system("cls");
	printf("\n\n                 [ RESULT ]\n\n\n");

	if (*isHighScore == TRUE)
	{
		*saveScore = abs(*saveScore);

		if (isBlock)
		{
			if (blockCnt == 1)
				strcpy_s(fileName, "./HighestScore_Block1.dat");
			else
				strcpy_s(fileName, "./HighestScore_Block2.dat");
		}
		else
			strcpy_s(fileName, "./HighestScore_Basic.dat");

		fopen_s(&openFp, fileName, "wb");
		if (openFp == NULL)
		{
			puts("FileError!");
			exit(1);
			// return FALSE;
		}
		fwrite(saveScore, sizeof(int), 1, openFp);	// ���̳ʸ� ������ fwrite�� �����!
		fclose(openFp);

		printf("\n>> Congratulations!\n>> You get a New High Score\n\n Score : %d\n\n", *saveScore);
	}
	else
	{
		printf("\n>> You're Score\n\nscore : %d\n\n", *saveScore);
	}

	printf("\n\n\n\n>> Select Menu\n\n[ OPTION ]\n- Go to Main, Push '1'\n- Start New Game, Push '2'\n- Exit Game, Push 'AnyKey'\n\nInput : ");

	inputNum = _getch();

	if (inputNum == inputNum_1)	// ����ȭ��
	{
		if (isSoundEffect) sndPlaySoundA(".\\sound\\highUp.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
		*checkPlay = mainScene;
		*isPlay = TRUE;
		puts("Main");
	}
	else if (inputNum == inputNum_2)	// ����ȭ��
	{
		*checkPlay = gameScene;
		*isPlay = TRUE;
		puts("New Game");
	}
	else
	{
		if (isSoundEffect) sndPlaySoundA(".\\sound\\highDown.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
		*checkPlay = gameExit;
		*isPlay = FALSE;
		puts("Exit");
	}
	Sleep(200);
}