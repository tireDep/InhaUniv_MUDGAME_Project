#include "BasicHeader.h"
#include "GameScreenHeader.h"

int Update();
bool CheckGameContinue(int(*mapArr)[4]);
void PrintNewInput(int(*mapArr)[4], char *string);

int main()
{
	srand((unsigned)time(NULL));
	system("mode con cols=39 lines=37");

	// todo/Maybe : bgm �߰�, ��ֹ� or �� ũ�� Ȯ��
	// todo : ����ȭ�� �� Ʃ�丮��

	// todo
	// - ���� �� �ִ� �ְ� ������ ��, ���� ����
	// - ���� ���, �ְ��� ���
	Update();

	// todo : ���� ��� �� ���ھ// ����
}

int Update()
{
	int inputNum = 0;
	int checkCanMove = 0;
	int checkGameOver = 0;

	int mapArr[BASICARRSIZE][BASICARRSIZE] = { 0 };

	SetStartMap(mapArr, 0);
	PrintArr(mapArr, "Start");

	while (1)
	{
		PlayerInput(mapArr, &checkCanMove, &checkGameOver);

		if (checkCanMove == 27)	// Pause
		{
			// 27 : esc Ascii, 1 : 1 Ascii
			printf(">>Pause\n\nIf You Finish Game, push 'Esc'\nContinue Game, push 'AnyKey'\nInput : ");
			if (CheckGameContinue(mapArr))
				return 0;
			else
				continue;
		}

		if (checkCanMove == 0 && checkGameOver == BASICARRSIZE * BASICARRSIZE)	// GameOver
		{
			printf("\n>> GameOver\n\nIf You Finish Game, push 'Esc'\nRevert Game, push 'AnyKey'\nInput : ");
			if (CheckGameContinue(mapArr))
				return 0;
			else
				continue;
		}

		if (checkCanMove != 0)	// Can Move
		{
			SetStartMap(mapArr, 1);
			PrintArr(mapArr, "NewBlock");
		}
		else // Can't Move
		{
			PrintNewInput(mapArr, "\n>> Can't Move\n\nReady to New Input : ");
			continue;
		}
	}
}

bool CheckGameContinue(int (*mapArr)[4])
{
	if (_getch() == 27)
	{
		printf("1\n\n>> Exit Game\n\n");
		return TRUE;
	}
	else
	{
		PrintNewInput(mapArr, "AnyKey\n\n>> Revert Game\n\nReady to New Input : ");
		return FALSE;
	}
}

void PrintNewInput(int (*mapArr)[4], char *string)
{
	printf("%s", string);
	for (int i = 5; i > 0; i--)
	{
		Sleep(500);
		printf("%d ", i);
	}
	PrintArr(mapArr, "NewInput");
}