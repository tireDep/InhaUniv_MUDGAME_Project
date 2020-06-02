#include<stdio.h>
#include<conio.h>	// _getch()
#include<stdlib.h>
#include<time.h>

#include<Windows.h>

#define ARRSIZE 4

void PrintArr(int(*mapArr)[ARRSIZE]);

int main()
{
	system("mode con cols=80 lines=25");
	int posX = 0, posY = 0, randVal = 0;
	srand((unsigned)time(NULL));
	int mapArr[ARRSIZE][ARRSIZE] = { 0 };

	int check = 0;
	while (1)
	{
		check++;
		posX = rand() % ARRSIZE;
		posY = rand() % ARRSIZE;
		// --------------------------
		randVal = rand() % 2;
		if (randVal == 0)
			randVal = 2;
		else if (randVal == 1)
			randVal = 4;
		// ----------------------
		if (mapArr[posY][posX] != 0)
		{
			check--;
			continue;
		}
		else
			mapArr[posY][posX] = randVal;
		
		if (check > 1)
			break;
	}
	
	// 키 입력 구분
	// 방향키는 2바이트기 때문에 리턴값이 두번
	int userInput = 0;
	userInput = _getch();
	if (userInput == 224)
	{
		userInput = _getch();
		switch (userInput)
		{
		case 72:
			printf("up\n");
			break;

		case 80:
			printf("down\n");
			break;

		case 75:
			printf("left\n");
			break;

		case 77:
			printf("right\n");
			break;

		default:
			break;
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

	PrintArr(mapArr);

}

void PrintArr(int (*mapArr)[ARRSIZE])
{
	for (int i = 0; i < ARRSIZE; i++)
	{
		for (int j = 0; j < ARRSIZE; j++)
		{
			printf("%d ", mapArr[i][j]);
		}
		puts("");
	}
}