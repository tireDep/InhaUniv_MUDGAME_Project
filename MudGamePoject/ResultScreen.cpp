#include "BasicHeader.h"
#include "ResultScreenHeader.h"

bool ResultScreen(bool *isHighScore, bool *isPlay, int *saveScore, int *checkPlay)
{
	FILE *openFp = NULL;
	int inputNum = 0;
	printf("AnyKey\n\n");
	system("cls");

	if (*isHighScore == TRUE)
	{
		*saveScore = abs(*saveScore);
		fopen_s(&openFp, "HighestScore.dat", "wb");
		if (openFp == NULL)
		{
			puts("FileError!");
			return FALSE;
		}
		fwrite(saveScore, sizeof(int), 1, openFp);	// ���̳ʸ� ������ fwrite�� �����!
		fclose(openFp);

		printf("\n\n                 [ RESULT ]\n\n\n");
		printf("\n>> Congratulations!\n>> You get a New High Score\n\n Score : %d\n\n", *saveScore);
	}
	else
	{
		system("cls");
		printf("\n\n                 [ RESULT ]\n\n\n");
		printf("\n>> You're Score\n\nscore : %d\n\n", *saveScore);
	}

	printf("\n\n\n\n>> Select Menu\n\n[ OPTION ]\n- Go to Main, Push '1'\n- Start New Game, Push '2'\n- Exit Game, Push 'AnyKey'\n\nInput : ");

	inputNum = _getch();
	if (inputNum == inputNum_1)	// ����ȭ��
	{
		puts("1");
		*checkPlay = mainScene;
		*isPlay = TRUE;
	}
	else if (inputNum == inputNum_2)	// ����ȭ��
	{
		*checkPlay = gameScene;
		*isPlay = TRUE;
	}
	else
	{
		puts("Exit");
		*checkPlay = gameExit;
		*isPlay = FALSE;
	}

	// ����ȭ�� or ����ȭ�� or ���� ���� �߰�
}