#include "BasicHeader.h"
#include "MainResultHeader.h"

void MainScreen(int *checkPlay)
{
	int inputNum = 0;
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n");
	printf("         ___     ___     ___     ___  \n");
	printf("       || 2 |  || 0 |  || 4 |  || 8 | \n");
	printf("       ||___|  ||___|  ||___|  ||___| \n");
	printf("       |/___|  |/___|  |/___|  |/___| \n");
	printf("\n\n\n\n\n\n\n");

	printf("             [ 1. GameStart ]\n\n\n");
	printf("             [ 2. Tutorial  ]\n\n\n\n\n\n");

	printf("         Press Another Key is Exit...\n\n");

	inputNum = _getch();

	if (inputNum == inputNum_1)
		*checkPlay = gameScene;	// ���ӽ��� ���ý�

	else if (inputNum == inputNum_2)
		TutorialScreen(checkPlay, inputNum);

	else
		*checkPlay = gameExit;
}

void TutorialScreen(int *checkPlay, int inputNum)
{
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
}

// ------------------------------------------------------------------------------------------------------------

bool ResultScreen(bool *isHighScore, bool *isPlay, int *saveScore, int *checkPlay)
{
	FILE *openFp = NULL;
	int inputNum = 0;
	printf("AnyKey\n\n");
	Sleep(200);
	system("cls");
	printf("\n\n                 [ RESULT ]\n\n\n");

	if (*isHighScore == TRUE)
	{
		*saveScore = abs(*saveScore);
		fopen_s(&openFp, "HighestScore.dat", "wb");
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
		*checkPlay = gameExit;
		*isPlay = FALSE;
		puts("Exit");
	}
	Sleep(200);
}