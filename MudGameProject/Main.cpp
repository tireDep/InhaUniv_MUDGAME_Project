#include "BasicHeader.h"
#include "GameScreenHeader.h"

int Update();
bool CheckGameContinue(int(*mapArr)[4]);
void PrintNewInput(int(*mapArr)[4], char *string);

int main()
{
	srand((unsigned)time(NULL));
	system("mode con cols=39 lines=37");

	// todo/Maybe : bgm 추가, 장애물 or 맵 크기 확장
	// todo : 메인화면 및 튜토리얼

	// todo
	// - 만들 수 있는 최고 숫자일 때, 게임 종료
	// - 점수 계산, 최고점 계산
	Update();

	// todo : 점수 계산 및 스코어링// 미정
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