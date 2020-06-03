#include "BasicHeader.h"
#include "GameScreenHeader.h"

int main()
{
	system("mode con cols=39 lines=23");

	srand((unsigned)time(NULL));
	
	int checkCanMove = 0;

	int mapArr[BASICARRSIZE][BASICARRSIZE] = { 0 };

	SetStartMap(mapArr, 0);
	PrintArr(mapArr, "Start");

	while (1)
	{
		PlayerInput(mapArr, &checkCanMove);
		if (checkCanMove != 0)
		{
			SetStartMap(mapArr, 1);
			PrintArr(mapArr, "NewBlock");
		}
		else
		{
			puts("이동불가능, 재입력");
			continue;
		}
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
