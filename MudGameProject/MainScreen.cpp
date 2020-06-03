#include "BasicHeader.h"

int MainScreen()
{
	system("mode con cols=50 lines=25");

	int inputNum = 0;
	printf("     2048     \n");
	printf("0. 튜토리얼\n1. 플레이\n2. 종료\n");
	printf("메뉴 선택 : ");
	scanf_s("%d", &inputNum);

	return inputNum;
}