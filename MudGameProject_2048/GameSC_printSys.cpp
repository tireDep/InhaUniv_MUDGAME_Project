#include "BasicHeader.h"
#include "GameScreen.h"
#include "Menu.h"

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
			else if (mapArr[i][j] == 1)
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