#include "BasicHeader.h"
#include "GameScreenHeader.h"

void SetStartMap(int(*mapArr)[BASICARRSIZE], int check)
{
	int posX = 0, posY = 0, randVal = 0;

	while (1)
	{
		check++;
		posX = rand() % BASICARRSIZE;
		posY = rand() % BASICARRSIZE;

		randVal = rand() % 2;
		if (randVal == 0)
			randVal = 2;
		else if (randVal == 1)
			randVal = 4;

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

// todo : 추후 리팩토링 다시할 예정
void PlayerInput(int(*mapArr)[BASICARRSIZE], int *checkCanMove, int *checkGameOver)
{
	*checkCanMove = 0;
	*checkGameOver = 0;

	int deleteInput = 0;
	int userInput = 0;

	if (_kbhit())
	{
		deleteInput = _getch();
		while (1)
		{
			if (deleteInput == 224)
			{
				deleteInput = _getch();
				if (deleteInput == 72 || deleteInput == 75 || deleteInput == 77 || deleteInput == 80)
					break;
			}
			else
				break;
		}
	}

	printf("\nPush Your Arrow Btn : ");
	userInput = _getch();

	if (userInput == 27)
	{
		puts("Esc\n");
		*checkCanMove = 27;
		return;
	}

	if (userInput == 224)
	{
		userInput = _getch();
		switch (userInput)
		{
		case 72:
			// ------------------------------------------------
			for (int i = 0; i < BASICARRSIZE; i++)
			{
				for (int j = 0; j < BASICARRSIZE - 1; j++)
				{
					if (IsCanMove(mapArr, j, i, checkCanMove, checkGameOver, plusPos, setZero))
						return;
				}
				if (mapArr[BASICARRSIZE-1][i] != 0)	// 맨 마지막 값 저장
					(*checkGameOver)++;
			}
			// ------------------------------------------------
			for (int posX = 0; posX < BASICARRSIZE; posX++)
			{
				for (int posY = 0; posY < BASICARRSIZE; posY++)
				{
					if (posY == 0)
						continue;
					MoveToInput(mapArr, &posY, &posX, upMove, stayMove, setZero, minusPos, upDownPos);
				}
				SetAbsVal_UpDown(mapArr, posX);
			}
			PrintArr(mapArr, "Move to Up");
			break;

		case 80:
			// -------------------------------------------------------
			for (int i = 0; i < BASICARRSIZE; i++)
			{
				for (int j = BASICARRSIZE; j > 0; j--)
				{
					if (j == BASICARRSIZE)
						continue;

					if (IsCanMove(mapArr,j,i,checkCanMove,checkGameOver,minusPos,setZero))
						return;
				}
				if (mapArr[BASICARRSIZE - 1][i] != 0)	// 맨 마지막 값 저장
					(*checkGameOver)++;
			}
			// ------------------------------------------------
			for (int posX = 0; posX < BASICARRSIZE; posX++)
			{
				for (int posY = BASICARRSIZE; posY >= 0; posY--)
				{
					if (posY >= BASICARRSIZE - downMove)
						continue;
					MoveToInput(mapArr, &posY, &posX, downMove, stayMove, setArrSize, plusPos, upDownPos);
				}
				SetAbsVal_UpDown(mapArr, posX);
			}
			PrintArr(mapArr, "Move to Down");
			break;

		case 75:
			// -------------------------------------------------------
			for (int i = 0; i < BASICARRSIZE; i++)
			{
				for (int j = 0; j < BASICARRSIZE - 1; j++)
				{
					if (IsCanMove(mapArr, i, j, checkCanMove, checkGameOver, setZero, plusPos))
						return;
				}
				if (mapArr[BASICARRSIZE - 1][i] != 0)	// 맨 마지막 값 저장
					(*checkGameOver)++;
			}
			// ------------------------------------------------
			for (int posY = 0; posY < BASICARRSIZE; posY++)
			{
				for (int posX = 0; posX < BASICARRSIZE; posX++)
				{
					if (posX == 0)
						continue;
					MoveToInput(mapArr, &posY, &posX, stayMove, leftMove, setZero, minusPos, leftRightPos);
				}
				SetAbsVal_RightLeft(mapArr, posY);
			} // for()
			PrintArr(mapArr, "Move to Left");
			break;

		case 77:
			// ------------------------------------------------
			for (int i = 0; i < BASICARRSIZE; i++)
			{
				for (int j = BASICARRSIZE; j > 0; j--)
				{
					if (j == BASICARRSIZE)
						continue;

					if (IsCanMove(mapArr, i, j, checkCanMove, checkGameOver, setZero, minusPos))
						return;
				}
				if (mapArr[BASICARRSIZE - 1][i] != 0)	// 맨 마지막 값 저장
					(*checkGameOver)++;
			}
			// ------------------------------------------------
			for (int posY = 0; posY < BASICARRSIZE; posY++)
			{
				for (int posX = BASICARRSIZE; posX >= 0; posX--)
				{
					if (posX >= BASICARRSIZE - rightMove)
						continue;
					MoveToInput(mapArr, &posY, &posX, stayMove, rightMove, setArrSize, plusPos, leftRightPos);
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

bool IsCanMove(int (*mapArr)[BASICARRSIZE], int posY, int posX, int *checkCanMove, int *checkGameOver, int moveY, int moveX)
{
	if (mapArr[posY][posX] == 0 && mapArr[posY + moveY][posX + moveX] != 0)
		(*checkCanMove)++;
	if (mapArr[posY][posX] == mapArr[posY + moveY][posX + moveX] && mapArr[posY][posX] != 0)
		(*checkCanMove)++;
	// 이동 가능 체크

	if (mapArr[posY][posX] != 0)
		(*checkGameOver)++;
	// 게임오버 체크
	// 마지막 위치의 값은 함수 밖에서 체크되고 있음에 유의
	// 후에 재작성 해볼것
	
	if (checkCanMove == 0 && (*checkGameOver) == 16)
		return TRUE;
	if (checkCanMove == 0)
		return TRUE;

	return FALSE;
}

void MoveToInput(int(*mapArr)[BASICARRSIZE], int *posY, int *posX, int moveY, int moveX, int setStart, int setNext, int moveTo)
{
	if (mapArr[*posY][*posX] != 0) //&& mapArr[posY][posX] != 1)	// 값이 있는 경우
	{
		if (mapArr[*posY + moveY][*posX + moveX] == 0)	// 앞 칸이 비었을 경우
		{
			mapArr[*posY + moveY][*posX + moveX] = mapArr[*posY][*posX];
			mapArr[*posY][*posX] = setZero;

			if (moveTo == upDownPos)
				*posY = setStart;
			else
				*posX = setStart;
		}
		else if (mapArr[*posY + moveY][*posX + moveX] == mapArr[*posY][*posX])	// 앞 칸의 숫자와 현재 칸의 숫자가 같을 경우
		{
			mapArr[*posY + moveY][*posX + moveX] = -(2 * mapArr[*posY][*posX]);
			mapArr[*posY][*posX] = setZero;

			if (moveTo == upDownPos)
				*posY += setNext;
			else
				posX += setNext;
		}
	}
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
	Sleep(200);
	system("cls");
	printf("\n   [123456score] 2048 [higestscore]  \n\n\n");
	printf(" >> Now status '%s'\n\n", string);
	for (int i = 0; i < BASICARRSIZE; i++)
	{
		puts("  -------- -------- -------- -------- ");
		puts(" |        |        |        |        | ");
		for (int j = 0; j < BASICARRSIZE; j++)
		{
			checkNum = 0;
			//if (mapArr[i][j] == 1)
			//{
			//	printf(" |  Block  ");
			//}
			//else
			//{
			while (pow(2, checkNum) != mapArr[i][j] && mapArr[i][j] != 0)
			{
				checkNum++;
			}
			printf(" ");
			TextColor(WHITE, BLACK);
			printf("|");
			TextColor(WHITE - checkNum, BLACK + checkNum);
			printf("%6d ", mapArr[i][j]);
			//}
		}
		printf(" ");
		TextColor(WHITE, BLACK);
		puts("|\n |        |        |        |        |");
	}
	puts("  -------- -------- -------- --------");
}

void TextColor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}