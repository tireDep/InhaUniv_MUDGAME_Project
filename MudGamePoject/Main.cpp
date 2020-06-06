#include "BasicHeader.h"
#include "GameScreenHeader.h"
#include "ResultScreenHeader.h"

int main()
{
	srand((unsigned)time(NULL));

	bool isPlay = TRUE;
	bool isHighScore = TRUE;
	int nowScore = 0;
	int highestScore = 0;
	int saveScore = 0;
	int checkPlay = startGame;

	system("mode con cols=44 lines=41");
	CursorView(0);

	// todo : ����ȭ�� �� Ʃ�丮��
	// +) Maybe : BGM, ��ŷ

	// todo : Ʃ�丮��
	// - text ���·� �÷��� ��� ���
	// - �÷��� ���
	/*
	--> ����Ű�� �Է��ؼ� ���ں���� �̵���ų �� ����(�����¿�)
	����
	��2��
	����

	--> ���� ���ں���� ���� ���, ���� ����� ������
	��2��2 => ���2+2 => ����4

	--> �� �̻� ������ �� ���ų�,((?)�ְ� ���ڸ� ���� ���) ���� ����

	*/

	// todo : ���� ȭ��
	// +) Maybe : ��ֹ� ���� ��, �� ũ�� Ȯ��, ��ŷ, �̵� O,X �� ȿ����

	while (1)
	{
		if (checkPlay == gameExit)
			break;

		if (checkPlay == mainScene)
		{
			// ����ȭ��
			system("cls");
			int inputNum = 0;
			printf("\n\n\n\n\n\n\n\n\n");
			printf("         ___     ___     ___     ___  \n");
			printf("       || 2 |  || 0 |  || 4 |  || 8 | \n");
			printf("       ||___|  ||___|  ||___|  ||___| \n");
			printf("       |/___|  |/___|  |/___|  |/___| \n");
			printf("\n\n\n\n\n\n\n");

			printf("             [ 1. GameStart ]\n\n\n");
			printf("             [ 2. Tutorial  ]\n\n\n\n\n\n");

			printf("         Press Another Key is Exit...\n\n");

			inputNum = _getch();

			if (inputNum == inputNum_1)
				checkPlay = gameScene;	// ���ӽ��� ���ý�

			else if (inputNum == inputNum_2)
			{
				// Ʃ�丮��
				system("cls");
				printf("\n\n                 [ TUTORIAL ]\n\n\n");
				// checkPlay = tutorialScene;
				
				printf(">> ���Ӽ���\n\n");
				printf("- ���� ���ں���� ����\n  ū ���ڸ� ����� ����\n\n\n");

				printf(">> ���ӹ��\n\n");
				printf("- ����Ű��             ���� \n");
				printf("  ���ں����           ���� \n");
				printf("  �̵���ų �� ����     ���� \n");

				printf("\n- ���� ���ں���� ���� ���,\n  �������鼭 ������ ���� �� ����\n");
				printf("\n  �� : ��2��2 => ���2+2 => ����4\n\n\n");

				printf(">> �Է�Ű\n\n- �̵� : ��, ��, ��, ��\n\n- �Ͻ����� : ESC\n\n\n");
				printf(">> ���ӿ���\n\n- ��� ĭ�� ���� ����� �ְ�,\n  �ش� �������� �̵��� �� ���� ��\n\n\n");
				// printf("\n- �־��� �ʿ��� ���� �� �ִ�\n  ���� ū ���ڸ� ������� ��\n\n  4x4 ���� : 131,072\n\n\n");

				printf("    [ Input AnyKey, You Can Go To Main ]\n");
				inputNum = _getch();
			if (inputNum != NULL)
				checkPlay = mainScene;
			}
			else
				checkPlay = gameExit;
		}

		if (checkPlay == gameScene)
		{
			SetValue(&nowScore, &highestScore, &saveScore, &checkPlay, &isPlay, &isHighScore);
			Start(&highestScore);
			Update(&checkPlay, &saveScore, &nowScore, &highestScore);

			if (checkPlay == gameScene)
			{
				printf("ReStart\n\n>> ReStart Game\n\nReady to New Game : ");
				for (int i = 5; i > 0; i--)
				{
					Sleep(100);
					printf("%d ", i);
				}
			}
		}

		if (checkPlay == resultScene)
		{
			if (saveScore < 0)
			{
				isHighScore = TRUE;
				ResultScreen(&isHighScore, &isPlay, &saveScore, &checkPlay);
				if (!isPlay)
					break;
				else
					continue;
			}
			else
			{
				isHighScore = FALSE;
				ResultScreen(&isHighScore, &isPlay, &saveScore, &checkPlay);
				if (!isPlay)
					break;
				else
					continue;
			}
		}
	}	// while()

	printf("\n\n\n              [ Game Exit ]\n\n");
	_getch();
	return 0;

	// todo : ���� ���� ȭ��
	// +) Maybe : ��ŷ
}
