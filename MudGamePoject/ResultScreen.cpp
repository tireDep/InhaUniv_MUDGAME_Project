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
		fwrite(saveScore, sizeof(int), 1, openFp);	// 바이너리 파일은 fwrite로 써야함!
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
	if (inputNum == inputNum_1)	// 메인화면
	{
		puts("1");
		*checkPlay = mainScene;
		*isPlay = TRUE;
	}
	else if (inputNum == inputNum_2)	// 게임화면
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

	// 시작화면 or 게임화면 or 종료 조건 추가
}