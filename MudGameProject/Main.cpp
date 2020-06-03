#include "BasicHeader.h"

void SetStartMap(int (*mapArr)[BASICARRSIZE], int check);
void PlayerInput(int (*mapArr)[BASICARRSIZE]);

int MoveTo_UpDown(int(*mapArr)[BASICARRSIZE], int posY, int posX, int moveY, int moveX, int setStart, int setNext);
int MoveTo_RightLeft(int(*mapArr)[BASICARRSIZE], int posY, int posX, int moveY, int moveX, int setStart, int setNext);

void SetAbsVal_UpDown(int(*mapArr)[BASICARRSIZE], int posX);
void SetAbsVal_RightLeft(int(*mapArr)[BASICARRSIZE], int posY);

void PrintArr(int(*mapArr)[BASICARRSIZE], char *string);
void TextColor(int foreground, int background);

int main()
{
	system("mode con cols=39 lines=23");

	srand((unsigned)time(NULL));
	bool isPrinting = false;
	int mapArr[BASICARRSIZE][BASICARRSIZE] = { 0 };

	SetStartMap(mapArr, 0);
	PrintArr(mapArr, "Start");

	while (1)
	{
		PlayerInput(mapArr);
		Sleep(250);
		SetStartMap(mapArr, 1);
		PrintArr(mapArr, "NewBlock");
	}

	/*
	참고 아스키 코드
	w : 87, 119
	a : 65, 97
	s : 83, 115
	d : 68, 100

	t : 84, 116
	r : 82, 114

	esc : 27
	*/
}

void SetStartMap(int (*mapArr)[BASICARRSIZE], int check)
{ 
	int posX = 0, posY = 0, randVal = 0;

	while (1)
	{
		check++;
		posX = rand() % BASICARRSIZE;
		posY = rand() % BASICARRSIZE;
		// --------------------------
		randVal = rand() % 2;
		if (randVal == 0)
			randVal = 2;
		else if (randVal == 1)
			randVal = 4;
		// ----------------------
		if (mapArr[posY][posX] != 0 && check >= 1)
		{
			check--;
			continue;
		}
		else if (mapArr[posY][posX] == 0 && check == 2)
		{
			mapArr[posY][posX] = randVal;
		}
		else
			mapArr[posY][posX] = randVal;

		if (check == 2)
			break;
	}
}

void PlayerInput(int(*mapArr)[BASICARRSIZE])
{
	int userInput = 0;
	userInput = _getch();

	if (userInput == 224)
	{
		userInput = _getch();
		switch (userInput)
		{
		case 72:
			// 게임오버 조건 추가
			for (int posX = 0; posX < BASICARRSIZE; posX++) // UP, LEFT
			{
				for (int posY = 0; posY < BASICARRSIZE; posY++)
				{
					if (posY == 0)
						continue;
					posY = MoveTo_UpDown(mapArr, posY, posX, upMove, stayMove, setZero, minusPos);
				}
				SetAbsVal_UpDown(mapArr,posX);
			}
			PrintArr(mapArr, "Move to Up");
			break;

		case 80:
			// 게임오버 조건 추가	
			for (int posX = 0; posX < BASICARRSIZE; posX++)	// DOWN, RIGHT
			{
				for (int posY = BASICARRSIZE; posY >= 0; posY--)
				{
					if (posY >= BASICARRSIZE - downMove)
						continue;
					posY = MoveTo_UpDown(mapArr, posY, posX, downMove, stayMove, setArrSize, plusPos);
				}
				SetAbsVal_UpDown(mapArr, posX);
			}
			PrintArr(mapArr, "Move to Down");
			break;

		case 75:
			// 게임오버 조건 추가
			for (int posY = 0; posY < BASICARRSIZE; posY++)
			{
				for (int posX = 0; posX < BASICARRSIZE; posX++)
				{
					if (posX == 0)
						continue;
					posX = MoveTo_RightLeft(mapArr, posY, posX, stayMove, leftMove, setZero, minusPos);
				}
				SetAbsVal_RightLeft(mapArr, posY);
			} // for()
			PrintArr(mapArr, "Move to Left");
			break;

		case 77:
			// 게임오버 조건 추가
			for (int posY = 0; posY < BASICARRSIZE; posY++)
			{
				for (int posX = BASICARRSIZE; posX >= 0; posX--)
				{
					if (posX >= BASICARRSIZE - rightMove)
						continue;
					posX = MoveTo_RightLeft(mapArr, posY, posX, stayMove, rightMove, setArrSize, plusPos);
				}
				SetAbsVal_RightLeft(mapArr, posY);
			} // for()
			PrintArr(mapArr, "Move to Right");
			break;

		default:
			break;
		}
	}
	else
	{
		printf("else Key\n");
	}
}

int MoveTo_UpDown(int (*mapArr)[BASICARRSIZE], int posY, int posX , int moveY, int moveX, int setStart, int setNext)
{
	if (mapArr[posY][posX] != 0) //&& mapArr[posY][posX] != 1)	// 값이 있는 경우
	{
		if (mapArr[posY + moveY][posX + moveX] == 0)	// 앞 칸이 비었을 경우
		{
			mapArr[posY + moveY][posX + moveX] = mapArr[posY][posX];
			mapArr[posY][posX] = setZero;
			posY = setStart;
		}
		else if (mapArr[posY + moveY][posX + moveX] == mapArr[posY][posX])	// 앞 칸의 숫자와 현재 칸의 숫자가 같을 경우
		{
			mapArr[posY + moveY][posX + moveX] = -(2 * mapArr[posY][posX]);
			mapArr[posY][posX] = setZero;
			posY += setNext;
		}
	}
	return posY;
}

int MoveTo_RightLeft(int(*mapArr)[BASICARRSIZE], int posY, int posX, int moveY, int moveX, int setStart, int setNext)
{
	if (mapArr[posY][posX] != 0)	// 값이 있는 경우
	{
		if (mapArr[posY + moveY][posX + moveX] == 0)	// 앞 칸이 비었을 경우
		{
			mapArr[posY + moveY][posX + moveX] = mapArr[posY][posX];
			mapArr[posY][posX] = setZero;
			posX = setStart;
		}
		else if (mapArr[posY + moveY][posX + moveX] == mapArr[posY][posX])	// 앞 칸의 숫자와 현재 칸의 숫자가 같을 경우
		{
			mapArr[posY + moveY][posX + moveX] = -(2 * mapArr[posY][posX]);
			mapArr[posY][posX] = setZero;
			posX += setNext;
		}
	}

	return posX;
}

void SetAbsVal_UpDown(int(*mapArr)[BASICARRSIZE], int posX)
{
	for (int i = 0; i < BASICARRSIZE; i++)
		mapArr[i][posX] = abs(mapArr[i][posX]);
}

void SetAbsVal_RightLeft(int(*mapArr)[BASICARRSIZE], int posY)
{
	for (int i = 0; i < BASICARRSIZE; i++)
		mapArr[posY][i] = abs(mapArr[posY][i]);
}

void PrintArr(int(*mapArr)[BASICARRSIZE], char *string)
{
	int checkNum = 0;
	Sleep(500);
	system("cls");
	printf("\n   [123456score] 2048 [higestscore]  \n\n\n");
	printf(" >> Now status '%s'\n", string);
	for (int i = 0; i < BASICARRSIZE; i++)
	{
		puts("  -------- -------- -------- -------- ");
		puts(" |        |        |        |        | ");
		for (int j = 0; j < BASICARRSIZE; j++)
		{
			checkNum = 0;
			if (mapArr[i][j] == 1)
			{
				printf(" |  Block  ");
			}
			else
			{
				printf(" |");
				while (pow(2,checkNum) != mapArr[i][j] && mapArr[i][j] != 0)
				{
					checkNum++;
				}
				TextColor(WHITE-checkNum, BLACK + checkNum);
				printf("%6d ", mapArr[i][j]);
				TextColor(WHITE, BLACK);
				// 색상 코드 추가
			}
		}
		puts(" |\n |        |        |        |        |");
	}
	puts("  -------- -------- -------- --------");
}

void TextColor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}