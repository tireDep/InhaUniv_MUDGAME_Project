#include "BasicHeader.h"
#include "GameScreenHeader.h"
#include "ResultScreenHeader.h"

int main()
{
	srand((unsigned)time(NULL));

	bool isPlay;
	bool isHighScore;
	int nowScore;
	int highestScore;
	int saveScore;
	int checkPlay = startGame;

	system("mode con cols=44 lines=41");
	CursorView(0);

	// todo : ����ȭ�� �� Ʃ�丮��
	// - ���� ����
	// - Ʃ�丮��
	// - ���� ����
	// +) Maybe : BGM, ��ŷ

	// todo : Ʃ�丮��
	// - text ���·� �÷��� ��� ���
	// - �÷��� ���
	/*
	--> ����Ű�� �Է��ؼ� ���ں����� �̵���ų �� ����(�����¿�)
	����
	��2��
	����

	--> ���� ���ں����� ���� ���, ���� ������ ������
	��2��2 => ���2+2 => ����4

	--> �� �̻� ������ �� ���ų�,((?)�ְ� ���ڸ� ���� ���) ���� ����

	*/
	// - �Է�Ű, �Ͻ�����Ű
	// - ����ȭ��(�ڷΰ���)

	// todo : ���� ȭ��
	// +) Maybe : ��ֹ� ���� ��, �� ũ�� Ȯ��, ��ŷ, �̵� O,X �� ȿ����

	while (1)
	{
		if (checkPlay == gameExit)
			break;

		if (checkPlay == mainScene)
		{
			system("cls");
			// ����ȭ�� ����
			int inputNum = 0;
			printf("\n\n\n\n\n\n\n\n\n");
			printf("         ___     ___     ___     ___  \n");
			printf("       || 2 |  || 0 |  || 4 |  || 8 | \n");
			printf("       ||___|  ||___|  ||___|  ||___| \n");
			printf("       |/___|  |/___|  |/___|  |/___| \n");
			printf("\n\n\n\n\n\n\n");

			printf("             [ 1. GameStart ]\n\n\n");
			printf("             [ 2. Tutorial  ]\n\n\n\n\n\n");

			printf("       Press Another Button is EXIT..\n\n");

			inputNum = _getch();
			/*			if (inputNum == inputNum_1)
			checkPlay = gameScene;	// ���ӽ��� ���ý�
			else if (inputNum == inputNum_2)
			{
			system("cls");
			// checkPlay = tutorialScene;
			printf("\n\n\n\n\n");
			printf("    [ Input AnyKey, You Can Go To Main ]");
			inputNum = _getch();
			if (inputNum != NULL)
			checkPlay = mainScene;
			}
			else
			checkPlay = gameExit;*/
		}
		checkPlay = gameScene;	// ���ӽ��� ���ý�
		if (checkPlay == gameScene)
		{
			SetValue(&nowScore, &saveScore, &checkPlay, &isPlay, &isHighScore);
			Start(&highestScore);
			Update(&checkPlay, &saveScore, &nowScore, &highestScore);

			if (checkPlay == gameScene)
			{
				printf("2\n\n>> ReStart Game\n\nReady to New Game : ");
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