#include "BasicHeader.h"

void SetStartMap(int (*mapArr)[BASICARRSIZE], int check);
void PlayerInput(int (*mapArr)[BASICARRSIZE]);
void InputMove_UpLeft(int(*mapArr)[BASICARRSIZE]);

void PrintArr(int(*mapArr)[BASICARRSIZE], char *string);
void TextColor(int foreground, int background);

int main()
{
	system("mode con cols=39 lines=23");

	srand((unsigned)time(NULL));
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
	���� �ƽ�Ű �ڵ�
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

void PlayerInput(int (*mapArr)[BASICARRSIZE])
{
	int userInput = 0;
	userInput = _getch();

	if (userInput == 224)
	{
		userInput = _getch();
		switch (userInput)
		{
		case 72:
			// ���ӿ��� ���� �߰�
			InputMove_UpLeft(mapArr);
			break;

		case 80:
			// ���ӿ��� ���� �߰�	
			for (int posX = 0; posX < BASICARRSIZE; posX++)	// DOWN, RIGHT
			{
				for (int posY = BASICARRSIZE; posY >= 0; posY--)
				{
					if (posY >= BASICARRSIZE - downMove)
						continue;

					if (mapArr[posY][posX] != 0)	// ���� �ִ� ���
					{
						if (mapArr[posY + downMove][posX] == 0)	// �� ĭ�� ����� ���
						{
							mapArr[posY + downMove][posX] = mapArr[posY][posX];
							mapArr[posY][posX] = 0;
							posY = BASICARRSIZE;
							continue;
						}
						else if (mapArr[posY + downMove][posX] == mapArr[posY][posX])	// �� ĭ�� ���ڿ� ���� ĭ�� ���ڰ� ���� ���
						{
							mapArr[posY + downMove][posX] = -(2 * mapArr[posY][posX]);
							mapArr[posY][posX] = 0;
							posY++;
							continue;
						}
					}
				}
				for (int i = 0; i < BASICARRSIZE; i++)
				{
					mapArr[i][posX] = abs(mapArr[i][posX]);
				}
			} // for()
			PrintArr(mapArr, "Move to Down");
			break;

		case 75:
			// ���ӿ��� ���� �߰�
			for (int posY = 0; posY < BASICARRSIZE; posY++)
			{
				for (int posX = 0; posX < BASICARRSIZE; posX++)
				{
					if (posX == 0)
						continue;

					if (mapArr[posY][posX] != 0)	// ���� �ִ� ���
					{
						if (mapArr[posY][posX - leftMove] == 0)	// �� ĭ�� ����� ���
						{
							mapArr[posY][posX - leftMove] = mapArr[posY][posX];
							mapArr[posY][posX] = 0;
							posX = 0;
							continue;
						}
						else if (mapArr[posY][posX - leftMove] == mapArr[posY][posX])	// �� ĭ�� ���ڿ� ���� ĭ�� ���ڰ� ���� ���
						{
							mapArr[posY][posX - leftMove] = -(2 * mapArr[posY][posX]);
							mapArr[posY][posX] = 0;
							posX--;
							continue;
						}
					}
				}
				for (int i = 0; i < BASICARRSIZE; i++)
				{
					mapArr[posY][i] = abs(mapArr[posY][i]);
				}
			} // for()
			PrintArr(mapArr, "Move to Left");
			break;

		case 77:
			// ���ӿ��� ���� �߰�
			for (int posY = 0; posY < BASICARRSIZE; posY++)
			{
				for (int posX = BASICARRSIZE; posX >= 0; posX--)
				{
					if (posX >= BASICARRSIZE - rightMove)
						continue;

					if (mapArr[posY][posX] != 0)	// ���� �ִ� ���
					{
						if (mapArr[posY][posX + rightMove] == 0)	// �� ĭ�� ����� ���
						{
							mapArr[posY][posX + rightMove] = mapArr[posY][posX];
							mapArr[posY][posX] = 0;
							posX = BASICARRSIZE;
							continue;
						}
						else if (mapArr[posY][posX + rightMove] == mapArr[posY][posX])	// �� ĭ�� ���ڿ� ���� ĭ�� ���ڰ� ���� ���
						{
							mapArr[posY][posX + rightMove] = -(2 * mapArr[posY][posX]);
							mapArr[posY][posX] = 0;
							posX++;
							continue;
						}
					}
				}
				for (int i = 0; i < BASICARRSIZE; i++)
				{
					mapArr[posY][i] = abs(mapArr[posY][i]);
				}
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

void InputMove_UpLeft(int(*mapArr)[BASICARRSIZE])
{
	for (int posX = 0; posX < BASICARRSIZE; posX++) // UP, LEFT
	{
		for (int posY = 0; posY < BASICARRSIZE; posY++)
		{
			if (posY == 0)
				continue;

			if (mapArr[posY][posX] != 0) //&& mapArr[posY][posX] != 1)	// ���� �ִ� ���
			{
				if (mapArr[posY - upMove][posX] == 0)	// �� ĭ�� ����� ���
				{
					mapArr[posY - upMove][posX] = mapArr[posY][posX];
					mapArr[posY][posX] = 0;
					posY = 0;
					continue;
				}
				else if (mapArr[posY - upMove][posX] == mapArr[posY][posX])	// �� ĭ�� ���ڿ� ���� ĭ�� ���ڰ� ���� ���
				{
					mapArr[posY - upMove][posX] = -(2 * mapArr[posY][posX]);
					mapArr[posY][posX] = 0;
					posY--;
					continue;
				}
			}
		}
		for (int i = 0; i < BASICARRSIZE; i++)
		{
			mapArr[i][posX] = abs(mapArr[i][posX]);
		}
	}
	PrintArr(mapArr, "Move to Up");
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
				// ���� �ڵ� �߰�
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