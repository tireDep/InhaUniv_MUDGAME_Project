#include "BasicHeader.h"

int MainScreen()
{
	system("mode con cols=50 lines=25");

	int inputNum = 0;
	printf("     2048     \n");
	printf("0. Ʃ�丮��\n1. �÷���\n2. ����\n");
	printf("�޴� ���� : ");
	scanf_s("%d", &inputNum);

	return inputNum;
}