#include "BasicHeader.h"
#include "GameScreen.h"

void SetValue(int *nowScore, int *highestScore, int *saveScore, int *checkPlay, int *inputMode, bool *isPlay, bool *isHighScore, bool *isBlock)
{
	*nowScore = 0;
	*highestScore = 0;
	*saveScore = 0;
	*inputMode = 0;

	*isPlay = TRUE;
	*isHighScore = TRUE;
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

void SetBlock(int(*mapArr)[BASICARRSIZE], int blockCnt)
{
	int posX = 0, posY = 0, blockNum = 1, check = 0;

	while (1)
	{
		check++;
		posX = rand() % BASICARRSIZE;
		posY = rand() % BASICARRSIZE;

		if (mapArr[posY][posX] != 0 && check >= 1)
		{
			check--;
			continue;
		}
		else if (mapArr[posY][posX] == 0 && check == 2)
		{
			mapArr[posY][posX] = blockNum;
		}
		else
			mapArr[posY][posX] = blockNum;

		if (check == blockCnt)
			break;
	}
}

// °ÿ : ∏Æ∆—≈‰∏µ
void SetAbsVal_UpDown(int(*mapArr)[BASICARRSIZE], int posX)
{
	for (int i = 0; i < BASICARRSIZE; i++)
		mapArr[i][posX] = abs(mapArr[i][posX]);
}

// °ÿ : ∏Æ∆—≈‰∏µ
void SetAbsVal_RightLeft(int(*mapArr)[BASICARRSIZE], int posY)
{
	for (int i = 0; i < BASICARRSIZE; i++)
		mapArr[posY][i] = abs(mapArr[posY][i]);
}
