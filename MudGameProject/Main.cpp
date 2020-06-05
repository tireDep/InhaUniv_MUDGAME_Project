#include "BasicHeader.h"
#include "GameScreenHeader.h"
#include "ResultScreenHeader.h"

int main()
{
	bool isPlay;
	bool isHighScore;
	int nowScore;
	int highestScore;
	int saveScore;
	int checkPlay = startGame;

	srand((unsigned)time(NULL));
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
	--> ����Ű�� �Է��ؼ� ���ں���� �̵���ų �� ����(�����¿�)
	����
	��2��
	����

	--> ���� ���ں���� ���� ���, ���� ����� ������
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
	
		else if (checkPlay == mainScene)
		{
			// ����ȭ�� ����
			system("cls");
			puts("------------------����ȭ�� �����ؾ���-----------");
			Sleep(500);
			
			checkPlay = gameScene;	// ���ӽ��� ���ý�
		}

		else if (checkPlay == gameScene)
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

		else if (checkPlay == resultScene)
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

	puts("\n\n>> Game Exit\n");
	_getch();
	return 0;

	// todo : ���� ���� ȭ��
	// +) Maybe : ��ŷ
}
