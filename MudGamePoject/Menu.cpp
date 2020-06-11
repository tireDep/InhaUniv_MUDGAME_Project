#include "Menu.h"

void GotoXY(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void EraseMenu(BYTE initX, BYTE initY, BYTE gap, BYTE maxMenu, BYTE menuString[][20])
{
	TextColor(WHITE, BLACK);
	for (int i = 0; i < maxMenu; i++)
	{
		GotoXY(initX, initY + (gap * i));
		printf("%s", menuString[i]);
	}
}

void TextColor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

BYTE SelectMenu(BYTE initX, BYTE initY, BYTE gap, BYTE maxMenu, BYTE menuString[][20])
{
	BYTE curMenu = 0;
	BYTE inputNum = 0;

	inputNum = _getch();
	GotoXY(initX, initY + (curMenu * gap));
	TextColor(BLACK, WHITE);
	printf("%s", menuString[curMenu]);
	if (inputNum == arrowStart)
		_getch();

	while (inputNum = _getch())
	{
		EraseMenu(initX, initY, gap, maxMenu, menuString);
		if (inputNum == enter || inputNum == spaceBar)
		{
			inputNum = curMenu + 49;
			break;
		}
		else if (inputNum == arrowStart)
		{
			switch (inputNum = _getch())
			{
			case arrowUp:
				curMenu--;
				break;
			case arrowDown:
				curMenu++;
				break;
			case arrowLeft:
				break;
			case arrowRight:
				break;
			}
			if (curMenu > maxMenu)
				curMenu = maxMenu - 1;
			else if (curMenu == maxMenu)
				curMenu = 0;
			GotoXY(initX, initY + (curMenu * gap));
			TextColor(BLACK, WHITE);
			printf("%s", menuString[curMenu]);
		}
		Sleep(50);
	}
	return inputNum;
}