#include<stdio.h>
#include<conio.h>	// _getch()
#include<time.h>
#include<stdlib.h>

#include<Windows.h>

#define ARRSIZE 4
#define MAXSCORE 131072 
// 3*3 = 1,024 / 4*4 = 131,072 / 5*5 = 67,108,864(65,536) / 6*6 이상은 숫자가 너무 큼
enum MovePos { rightMove = 1, leftMove = 1, upMove = 1, downMove = 1 };


void PrintArr(int(*mapArr)[ARRSIZE]);

int main()
{
	system("mode con cols=50 lines=25");

	srand((unsigned)time(NULL));
	int posX = 0, posY = 0, randVal = 0;
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
	
	mapArr[0][0] = 2;
	mapArr[1][0] = 2;
	mapArr[2][0] = 2;
	mapArr[3][0] = 2;
	mapArr[1][1] = 2;
	mapArr[3][1] = 2;

	mapArr[3][2] = 2;
	mapArr[3][3] = 2;
	PrintArr(mapArr);
	
	// 키 입력 구분
	// 방향키는 2바이트기 때문에 리턴값이 두번

	/*
	 0, 0 /  0, -1  /  0, 0
	-1, 0 /  0, 0   / +1, 0
	 0, 0 /  0, +1  /  0, 0
	*/

	int userInput = 0;
	userInput = _getch();
	if (userInput == 224)
	{
		userInput = _getch();
		switch (userInput)
		{
		case 72:
			printf("up\n");
			
			/*for (int i = upMove; i < ARRSIZE; i++)
			{
				for (int j = 0; j < ARRSIZE; j++)
				{
					if (mapArr[i][j] != 0 && i<ARRSIZE && j<ARRSIZE)
					{
						mapArr[i - upMove][j] = mapArr[i][j];
						mapArr[i][j] = 0;
					}
				}
			}*/

			for (int posX = 0; posX < ARRSIZE; posX++)
			{
				for (int posY = 0; posY < ARRSIZE; posY++)
				{
					if (posY == 0)
						continue;

					if (mapArr[posY][posX] != 0)	// 값이 있는 경우
					{
						if (mapArr[posY - upMove][posX] == 0)	// 앞 칸이 비었을 경우
						{
							mapArr[posY - upMove][posX] = mapArr[posY][posX];
							mapArr[posY][posX] = 0;
							posY = 0;
							continue;
						}
						else if (mapArr[posY - upMove][posX] == mapArr[posY][posX])	// 앞 칸의 숫자와 현재 칸의 숫자가 같을 경우
						{
							mapArr[posY - upMove][posX] = -(2 * mapArr[posY][posX]);
							mapArr[posY][posX] = 0;
							posY--;
							continue;
						}
					}
				}
				for (int i = 0; i < ARRSIZE; i++)
				{
					mapArr[i][posX] = abs(mapArr[i][posX]);
				}
				PrintArr(mapArr);
			} // for()
			break;

		case 80:
			printf("down\n");

			for (int posX = 0; posX < ARRSIZE; posX++)
			{
				for (int posY = ARRSIZE; posY >= 0; posY--)
				{
					if (posY >= ARRSIZE - downMove)
						continue;

					if (mapArr[posY][posX] != 0)	// 값이 있는 경우
					{
						if (mapArr[posY + downMove][posX] == 0)	// 앞 칸이 비었을 경우
						{
							mapArr[posY + downMove][posX] = mapArr[posY][posX];
							mapArr[posY][posX] = 0;
							posY = ARRSIZE;
							continue;
						}
						else if (mapArr[posY + downMove][posX] == mapArr[posY][posX])	// 앞 칸의 숫자와 현재 칸의 숫자가 같을 경우
						{
							mapArr[posY + downMove][posX] = -(2 * mapArr[posY][posX]);
							mapArr[posY][posX] = 0;
							posY++;
							continue;
						}
					}
				}
				for (int i = 0; i < ARRSIZE; i++)
				{
					mapArr[i][posX] = abs(mapArr[i][posX]);
				}
				PrintArr(mapArr);
			} // for()

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
	else
	{
		printf("else Key\n");
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
	// mapArr[3][3] = 1048;
	Sleep(250);
	system("cls");
	for (int i = 0; i < ARRSIZE; i++)
	{
		puts(" ------- ------- ------- -------");
		puts("|       |       |       |       | ");
		for (int j = 0; j < ARRSIZE; j++)
		{
			printf("| %5d ", mapArr[i][j]);
		}
		puts("|\n|       |       |       |       |");
	}
	puts(" ------- ------- ------- -------");
}