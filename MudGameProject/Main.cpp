#include "BasicHeader.h"
#include "GameScreenHeader.h"

int main()
{
	srand((unsigned)time(NULL));
	system("mode con cols=39 lines=28");

	int checkCanMove = 0;
	int checkGameOver = 0;
	int mapArr[BASICARRSIZE][BASICARRSIZE] = { 0 };

	SetStartMap(mapArr, 0);
	PrintArr(mapArr, "Start");

	while (1)
	{
		PlayerInput(mapArr, &checkCanMove, &checkGameOver);

		if (checkCanMove == 27)
		{
			puts("���� ����");
			return 0;
		}
		if (checkCanMove == 0 && checkGameOver == BASICARRSIZE * BASICARRSIZE)
		{
			puts("���ӿ���");
			// todo : ���ӿ��� ���� �������� �ۼ�
		}

		if (checkCanMove != 0)
		{
			SetStartMap(mapArr, 1);
			PrintArr(mapArr, "NewBlock");
		}
		else
		{
			puts(">> Can't Move");
			printf("Ready to New Input : ");
			for (int i = 5; i > 0; i--)
			{
				Sleep(500);
				printf("%d ", i);
			}
			PrintArr(mapArr, "NewInput");
			continue;
		}
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
