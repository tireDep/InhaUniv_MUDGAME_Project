#include "BasicHeader.h"
#include "StartResultScreen.h"

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
		fwrite(saveScore, sizeof(int), 1, openFp);	// 바이너리 파일은 fwrite로 써야함!
		fclose(openFp);

		printf("\n>> Congratulations!\n>> You get a New High Score\n\n Score : %d\n\n", *saveScore);
	}
	else
	{
		printf("\n>> You're Score\n\nscore : %d\n\n", *saveScore);
	}

	printf("\n\n\n\n>> Select Menu\n\n[ OPTION ]\n- Go to Main, Push '1'\n- Start New Game, Push '2'\n- Exit Game, Push 'AnyKey'\n\nInput : ");

	inputNum = _getch();

	if (inputNum == inputNum_1)	// 메인화면
	{
		if (isSoundEffect) sndPlaySoundA(".\\sound\\highUp.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
		*checkPlay = mainScene;
		*isPlay = TRUE;
		puts("Main");
	}
	else if (inputNum == inputNum_2)	// 게임화면
	{
		if (isSoundEffect) sndPlaySoundA(".\\sound\\highUp.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
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
