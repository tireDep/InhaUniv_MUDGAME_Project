#include "BasicHeader.h"
#include "GameScreenHeader.h"

int Update(int *checkPlay, int *saveScore)
{
	// todo : �ְ����� �ҷ��;���
	FILE *openFp = NULL;
	int prevScore = 0;
	int highestScore = 0;
	int nowScore = 0;

	if (_access("./HighestScore.dat", 00) == 0)	// ������ �����ϴ� ���
	{
		fopen_s(&openFp, "HighestScore.dat", "rb");	// ù ����� �������� x �̱� ������ rb+ // ���� ���� x
	}
	else
	{
		fopen_s(&openFp, "HighestScore.dat", "wb");
	}

	if (openFp == NULL)
	{
		puts("FileError!");
		return 0;
	}
	fread(&highestScore, sizeof(int), 1, openFp);	// ���̳ʸ� ������ fread�� �о�� ��!
	fclose(openFp);
	prevScore = highestScore;
	// ------------------------------------------------------------

	int inputNum = 0;
	int checkMaxNum = 0;
	int checkCanMove = 0;
	int checkGameOver = 0;
	int kbhitCnt = 0;

	int mapArr[BASICARRSIZE][BASICARRSIZE] = { 0 };

	SetNewNum(mapArr, 0);
	PrintArr(mapArr, "START", &kbhitCnt, &nowScore, &highestScore);
	// mapArr[1][1] = BASICARR_MAXNUM;
	while (1)
	{
		PlayerInput(mapArr, &checkCanMove, &checkGameOver, &checkMaxNum, &kbhitCnt, &nowScore, &highestScore);

		if (checkCanMove == 27)	// Pause
		{
			// continue : 1 / restart : 2 / exit : AnyKey
			printf(">> Pause\n\n[ OPTION ]\n- If You Continue Game, push '1'\n- ReStart Game, push '2'\n- Exit Game, push 'AntKey'\n\nInput : ");
			if (CheckGameContinue(mapArr, &kbhitCnt, checkPlay))
			{
				if (*checkPlay == 49)	// continue
				{
					PrintNewInput(mapArr, "1\n\n>> Continue Game\n\nReady to Continue : ", &kbhitCnt, &nowScore, &highestScore);
					continue;
				}
				else
					return 0; 
			}
			else
			{

				if (prevScore < highestScore)
					*saveScore = -highestScore;	// �ִ� ������ �˸��� ���� ����ȭ
				else
					*saveScore = nowScore;
				return 0;
			}
			// todo : �ְ����� ����_������ ���� �� ���
			// main���� �Ѱܼ� �ؾ��� �� ��?
		}

		if (checkCanMove == 0 && checkGameOver == BASICARRSIZE * BASICARRSIZE)	// GameOver
		{
			// continue : 1 / restart : 2 / exit : AnyKey
			printf("\n>> GameOver\n\n[ OPTION ]\n- If You Revert Game, push '1'\n- ReStart Game, push '2'\n- Exit Game, push 'AntKey'\n\nInput : ");
			if (CheckGameContinue(mapArr, &kbhitCnt, checkPlay))
			{
				if (*checkPlay == 49)
				{
					PrintNewInput(mapArr, "1\n\n>> Revert Game\n\nReady to Revert : ", &kbhitCnt, &nowScore, &highestScore);
					continue;
				}
				else
				{
					if (prevScore < highestScore)
						*saveScore = -highestScore;	// �ִ� ������ �˸��� ���� ����ȭ
					else
						*saveScore = nowScore;
					return 0;
				}
			}
			else
				return 0;
			// todo : �ְ����� ����_������ ���� �� ���
			// main���� �Ѱܼ� �ؾ��� �� ��?
		}

		if (checkMaxNum == BASICARR_MAXNUM)	// MaxNum in it
		{
			// restart : 1 or 2 / exit : AnyKey
			// �� : restart�� 2���̶� 1�� ������ 2������ ��µ�
			printf("\n>> Congratulations!\n>> You Made a MaxNumber!\n\n[ OPTION ]\n- Start New Game, push '1' or '2'\n- Finish Game, push 'AnyKey'\n\nInput : ");
			if (CheckGameContinue(mapArr, &kbhitCnt, checkPlay))
			{
				*checkPlay = 50;
				return 0;
			}
			else
			{

				if (prevScore < highestScore)
					*saveScore = -highestScore;	// �ִ� ������ �˸��� ���� ����ȭ
				else
					*saveScore = nowScore;
				return 0;
			}
			// todo : �ְ����� ����_������ ���� �� ���
			// main���� �Ѱܼ� �ؾ��� �� ��?
		}

		if (checkCanMove != 0)	// Can Move
		{
			SetNewNum(mapArr, 1);
			PrintArr(mapArr, "NewBlock", &kbhitCnt, &nowScore, &highestScore);
		}
		else // Can't Move
		{
			PrintNewInput(mapArr, "\n>> Can't Move\n\nReady to New Input : ", &kbhitCnt, &nowScore, &highestScore);
			continue;
		}
	}
}

void SetNewNum(int(*mapArr)[BASICARRSIZE], int check)
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

// todo : ���� �����丵 �ٽ��� ����
void PlayerInput(int(*mapArr)[BASICARRSIZE], int *checkCanMove, int *checkGameOver, int *checkMaxNum, int *kbhitCnt, int *nowScore, int *highestScore)
{
	*checkCanMove = 0;
	*checkGameOver = 0;
	*checkMaxNum = 0;

	int userInput = 0;

	CheckKbhitCnt(kbhitCnt);
	DeleteInput(kbhitCnt);

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
					if (IsCanMove(mapArr, j, i, checkCanMove, checkGameOver, checkMaxNum, plusPos, zeroPos))
						return;
				}
				if (mapArr[BASICARRSIZE-1][i] != 0)	// �� ������ �� ����
					(*checkGameOver)++;

				if (mapArr[BASICARRSIZE - 1][i] == BASICARR_MAXNUM)	// �ִ� Ȯ��
					(*checkMaxNum) = BASICARR_MAXNUM;
			}
			// ------------------------------------------------
			for (int posX = 0; posX < BASICARRSIZE; posX++)
			{
				for (int posY = 0; posY < BASICARRSIZE; posY++)
				{
					if (posY == 0)
						continue;
					MoveToInput(mapArr, &posY, &posX, upMove, stayMove, zeroPos, minusPos, upDownPos, nowScore, highestScore);
				}
				SetAbsVal_UpDown(mapArr, posX);
			}
			PrintArr(mapArr, "Move to Up", kbhitCnt, nowScore, highestScore);
			break;

		case 80:
			// -------------------------------------------------------
			for (int i = 0; i < BASICARRSIZE; i++)
			{
				for (int j = BASICARRSIZE; j > 0; j--)
				{
					if (j == BASICARRSIZE)
						continue;

					if (IsCanMove(mapArr,j,i,checkCanMove,checkGameOver, checkMaxNum, minusPos,zeroPos))
						return;
				}
				if (mapArr[BASICARRSIZE - 1][i] != 0)	// �� ������ �� ����
					(*checkGameOver)++;

				if (mapArr[BASICARRSIZE - 1][i] == BASICARR_MAXNUM)	// �ִ� Ȯ��
					(*checkMaxNum) = BASICARR_MAXNUM;
			}
			// ------------------------------------------------
			for (int posX = 0; posX < BASICARRSIZE; posX++)
			{
				for (int posY = BASICARRSIZE; posY >= 0; posY--)
				{
					if (posY >= BASICARRSIZE - downMove)
						continue;
					MoveToInput(mapArr, &posY, &posX, downMove, stayMove, arrSizePos, plusPos, upDownPos, nowScore, highestScore);
				}
				SetAbsVal_UpDown(mapArr, posX);
			}
			PrintArr(mapArr, "Move to Down", kbhitCnt, nowScore, highestScore);
			break;

		case 75:
			// -------------------------------------------------------
			for (int i = 0; i < BASICARRSIZE; i++)
			{
				for (int j = 0; j < BASICARRSIZE - 1; j++)
				{
					if (IsCanMove(mapArr, i, j, checkCanMove, checkGameOver, checkMaxNum, zeroPos, plusPos))
						return;
				}
				if (mapArr[i][BASICARRSIZE - 1] != 0)	// �� ������ �� ����
					(*checkGameOver)++;

				if (mapArr[i][BASICARRSIZE - 1] == BASICARR_MAXNUM)	// �ִ� Ȯ��
					(*checkMaxNum) = BASICARR_MAXNUM;
			}
			// ------------------------------------------------
			for (int posY = 0; posY < BASICARRSIZE; posY++)
			{
				for (int posX = 0; posX < BASICARRSIZE; posX++)
				{
					if (posX == 0)
						continue;
					MoveToInput(mapArr, &posY, &posX, stayMove, leftMove, zeroPos, minusPos, leftRightPos, nowScore, highestScore);
				}
				SetAbsVal_RightLeft(mapArr, posY);
			} // for()
			PrintArr(mapArr, "Move to Left", kbhitCnt, nowScore, highestScore);
			break;

		case 77:
			// ------------------------------------------------
			for (int i = 0; i < BASICARRSIZE; i++)
			{
				for (int j = BASICARRSIZE; j > 0; j--)
				{
					if (j == BASICARRSIZE)
						continue;

					if (IsCanMove(mapArr, i, j, checkCanMove, checkGameOver, checkMaxNum, zeroPos, minusPos))
						return;
				}
				if (mapArr[i][BASICARRSIZE - 1] != 0)	// �� ������ �� ����
					(*checkGameOver)++;

				if (mapArr[i][BASICARRSIZE - 1] == BASICARR_MAXNUM)	// �ִ� Ȯ��
					(*checkMaxNum) = BASICARR_MAXNUM;
			}
			// ------------------------------------------------
			for (int posY = 0; posY < BASICARRSIZE; posY++)
			{
				for (int posX = BASICARRSIZE; posX >= 0; posX--)
				{
					if (posX >= BASICARRSIZE - rightMove)
						continue;
					MoveToInput(mapArr, &posY, &posX, stayMove, rightMove, arrSizePos, plusPos, leftRightPos, nowScore, highestScore);
				}
				SetAbsVal_RightLeft(mapArr, posY);
			} // for()
			PrintArr(mapArr, "Move to Right", kbhitCnt, nowScore, highestScore);
			break;

		default:
			break;
		}
	}
	else
	{
		printf("Wrong Btn\n");
	}
}

bool IsCanMove(int (*mapArr)[BASICARRSIZE], int posY, int posX, int *checkCanMove, int *checkGameOver, int *checkMaxNum, int moveY, int moveX)
{
	if (mapArr[posY][posX] == 0 && mapArr[posY + moveY][posX + moveX] != 0)
		(*checkCanMove)++;
	if (mapArr[posY][posX] == mapArr[posY + moveY][posX + moveX] && mapArr[posY][posX] != 0)
		(*checkCanMove)++;
	// �̵� ���� üũ

	if (mapArr[posY][posX] != 0)
		(*checkGameOver)++;
	// ���ӿ��� üũ
	// ������ ��ġ�� ���� �Լ� �ۿ��� üũ�ǰ� ������ ����
	// �Ŀ� ���ۼ� �غ���

	if (mapArr[posY][posX] == BASICARR_MAXNUM)
		(*checkMaxNum) = BASICARR_MAXNUM;
	
	if (checkCanMove == 0 && (*checkGameOver) == 16)
		return TRUE;
	if (checkCanMove == 0)
		return TRUE;

	return FALSE;
}

void MoveToInput(int(*mapArr)[BASICARRSIZE], int *posY, int *posX, int moveY, int moveX, int setStart, int setNext, int moveTo, int *nowScore, int *highestScore)
{
	if (mapArr[*posY][*posX] != 0) //&& mapArr[posY][posX] != 1)	// ���� �ִ� ���
	{
		if (mapArr[*posY + moveY][*posX + moveX] == 0)	// �� ĭ�� ����� ���
		{
			mapArr[*posY + moveY][*posX + moveX] = mapArr[*posY][*posX];
			mapArr[*posY][*posX] = zeroPos;

			if (moveTo == upDownPos)
				*posY = setStart;
			else
				*posX = setStart;
		}
		else if (mapArr[*posY + moveY][*posX + moveX] == mapArr[*posY][*posX])	// �� ĭ�� ���ڿ� ���� ĭ�� ���ڰ� ���� ���
		{
			mapArr[*posY + moveY][*posX + moveX] = -(2 * mapArr[*posY][*posX]);
			mapArr[*posY][*posX] = zeroPos;

			// todo : ���� ���
			// ��������� ������ �� ��ŭ ������
			// �ְ����� ���� ���� �� �ʿ�
			*nowScore += abs(mapArr[*posY + moveY][*posX + moveX]);	// �ߺ� ��ħ �������� ����ó�� �ؼ� ���밪ȭ
			if (*nowScore > *highestScore)
			{
				*highestScore = *nowScore;
			}

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

void PrintArr(int(*mapArr)[BASICARRSIZE], char *string, int *kbhitCnt, int *nowScore, int *highestScore)
{
	// todo : ���� ���
	int checkNum = 0;
	Sleep(200);
	system("cls");
	printf("\n\n     [ NOW_SCORE ]  2048  [ HIGHSCORE ]");
	printf("\n    [%12d ]      [%12d ]  \n\n\n", *nowScore, *highestScore);
	printf(" >> Now status '%s'\n\n", string);
	for (int i = 0; i < BASICARRSIZE; i++)
	{
		CheckKbhitCnt(kbhitCnt);
		DeleteInput(kbhitCnt);
		puts("    -------- -------- -------- -------- ");
		puts("   |        |        |        |        | ");
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
			if(j == 0)
				printf("   ");
			else
				printf("  ");
			TextColor(WHITE, BLACK);
			printf("|");
			TextColor(WHITE - checkNum, BLACK + checkNum);
			printf("%6d", mapArr[i][j]);
			//}
		}
		printf("  ");
		TextColor(WHITE, BLACK);
		puts("|\n   |        |        |        |        |");
	}
	puts("    -------- -------- -------- --------");
}

void TextColor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

bool CheckGameContinue(int(*mapArr)[4], int *kbhitCnt, int *checkPlay)
{
	// continue : 1 / restart : 2 / exit : AnyKey
	int inputNum = 0;
	inputNum = _getch();

	if (inputNum == 49)
	{
		*checkPlay = 49;
		return TRUE;
	}
	else if (inputNum == 50)
	{
		*checkPlay = 50;
		return TRUE;
	}
	else
		return FALSE;
}

void CheckKbhitCnt(int *kbhitCnt)
{
	if (_kbhit())
		(*kbhitCnt)++;
}

void DeleteInput(int *kbhitCnt)
{
	int deleteInput = 0;
	rewind(stdin);

	while (*kbhitCnt>0)
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
		(*kbhitCnt)--;
	}
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