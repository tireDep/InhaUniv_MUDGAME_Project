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
		*checkPlay = gameScene;	// 게임시작 선택시

	else if (inputNum == inputNum_2)
		TutorialScreen(checkPlay, inputNum);

	else
		*checkPlay = gameExit;
}

void TutorialScreen(int *checkPlay, int inputNum)
{
	system("cls");
	printf("\n\n                 [ TUTORIAL ]\n\n\n");

	printf(">> 게임설명\n\n");
	printf("- 같은 숫자블록을 합쳐\n  큰 숫자를 만드는 게임\n\n\n");

	printf(">> 게임방법\n\n");
	printf("- 방향키로             □↑□ \n");
	printf("  숫자블록을           ←②→ \n");
	printf("  이동시킬 수 있음     □↓□ \n");

	printf("\n- 같은 숫자블록이 만날 경우,\n  합쳐지면서 점수를 얻을 수 있음\n");
	printf("\n  → : □2□2 => □□2+2 => □□□4\n\n\n");

	printf(">> 입력키\n\n- 이동 : ↑, ↓, ←, →\n\n- 일시정지 : ESC\n\n\n");
	printf(">> 게임오버\n\n- 모든 칸에 숫자 블록이 있고,\n  해당 방향으로 이동할 수 없을 때\n\n\n");
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
		*checkPlay = mainScene;
		*isPlay = TRUE;
		puts("Main");
	}
	else if (inputNum == inputNum_2)	// 게임화면
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