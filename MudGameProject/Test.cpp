#include<stdio.h>
#include<conio.h>	// _getch()
#include<time.h>
#include<stdlib.h>
#include<Windows.h>

#define ARRSIZE 4
#define MAXNUM 131072 
// 3*3 = 1,024 / 4*4 = 131,072 / 5*5 = 67,108,864(65,536) / 6*6 이상은 숫자가 너무 큼
enum MovePos { rightMove = 1, leftMove = 1, upMove = 1, downMove = 1 };

void PrintArr(int(*mapArr)[ARRSIZE], char *string);

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
	
	mapArr[0][0] = 1;
	mapArr[1][0] = 2;
	mapArr[2][0] = 2;
	mapArr[3][0] = 2;
	mapArr[1][1] = 2;
	mapArr[3][1] = 2;

	mapArr[3][2] = 2;
	mapArr[3][3] = 1;
	PrintArr(mapArr,"Start");
	
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

			// 게임오버 조건 추가
			for (int posX = 0; posX < ARRSIZE; posX++) // UP, LEFT
			{
				for (int posY = 0; posY < ARRSIZE; posY++)
				{
					if (posY == 0)
						continue;

					if (mapArr[posY][posX] != 0 && mapArr[posY][posX] != 1)	// 값이 있는 경우
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
				PrintArr(mapArr,"UpMove");
			} // for()
			break;

		case 80:
			printf("down\n");

			// 게임오버 조건 추가	
			for (int posX = 0; posX < ARRSIZE; posX++)	// DOWN, RIGHT
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
				PrintArr(mapArr,"DownMove");
			} // for()

			break;

		case 75:
			printf("left\n");

			// 게임오버 조건 추가
			for (int posY = 0; posY < ARRSIZE; posY++)
			{
				for (int posX = 0; posX < ARRSIZE; posX++)
				{
					if (posX == 0)
						continue;

					if (mapArr[posY][posX] != 0)	// 값이 있는 경우
					{
						if (mapArr[posY][posX - leftMove] == 0)	// 앞 칸이 비었을 경우
						{
							mapArr[posY][posX - leftMove] = mapArr[posY][posX];
							mapArr[posY][posX] = 0;
							posX = 0;
							continue;
						}
						else if (mapArr[posY][posX - leftMove] == mapArr[posY][posX])	// 앞 칸의 숫자와 현재 칸의 숫자가 같을 경우
						{
							mapArr[posY][posX - leftMove] = -(2 * mapArr[posY][posX]);
							mapArr[posY][posX] = 0;
							posX--;
							continue;
						}
					}
				}
				for (int i = 0; i < ARRSIZE; i++)
				{
					mapArr[posY][i] = abs(mapArr[posY][i]);
				}
				PrintArr(mapArr, "LeftMove");
			} // for()


			break;

		case 77:
			printf("right\n");

			  // 게임오버 조건 추가
			for (int posY = 0; posY < ARRSIZE; posY++)
			{
				for (int posX = ARRSIZE; posX >= 0; posX--)
				{
					if (posX >= ARRSIZE - rightMove)
						continue;

					if (mapArr[posY][posX] != 0)	// 값이 있는 경우
					{
						if (mapArr[posY][posX + rightMove] == 0)	// 앞 칸이 비었을 경우
						{
							mapArr[posY][posX + rightMove] = mapArr[posY][posX];
							mapArr[posY][posX] = 0;
							posX = ARRSIZE;
							continue;
						}
						else if (mapArr[posY][posX + rightMove] == mapArr[posY][posX])	// 앞 칸의 숫자와 현재 칸의 숫자가 같을 경우
						{
							mapArr[posY][posX + rightMove] = -(2 * mapArr[posY][posX]);
							mapArr[posY][posX] = 0;
							posX++;
							continue;
						}
					}
				}
				for (int i = 0; i < ARRSIZE; i++)
				{
					mapArr[posY][i] = abs(mapArr[posY][i]);
				}
				PrintArr(mapArr,"RightMove");
			} // for()

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

	// PrintArr(mapArr);

}

void PrintArr(int (*mapArr)[ARRSIZE], char *string)
{
	// mapArr[3][3] = 1048;
	Sleep(500);
	system("cls");
	printf("%s\n", string);
	for (int i = 0; i < ARRSIZE; i++)
	{
		puts(" ------- ------- ------- -------");
		puts("|       |       |       |       | ");
		for (int j = 0; j < ARRSIZE; j++)
		{
			if (mapArr[i][j] == 1)
			{
				printf("| Block ");
			}
			else
			{
				printf("| %5d ", mapArr[i][j]);
			}
		}
		puts("|\n|       |       |       |       |");
	}
	puts(" ------- ------- ------- -------");
}