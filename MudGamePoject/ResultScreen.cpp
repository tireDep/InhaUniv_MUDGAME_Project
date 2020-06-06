#include "BasicHeader.h"
#include "ResultScreenHeader.h"

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
		Sleep(200);
	}
	else if (inputNum == inputNum_2)	// ����ȭ��
	{
		*checkPlay = gameScene;
		*isPlay = TRUE;
		puts("New Game");
		Sleep(200);
	}
	else
	{
		*checkPlay = gameExit;
		*isPlay = FALSE;
		puts("Exit");
		Sleep(200);
	}

	// ����ȭ�� or ����ȭ�� or ���� ���� �߰�
}