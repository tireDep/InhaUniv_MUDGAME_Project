#include "BasicHeader.h"
#include "GameScreenHeader.h"

bool ResultScreen(bool *isHighScore, bool *isPlay, int *saveScore, int *checkPlay);
void SetValue(int *nowScore, int *saveScore, int *checkPlay, bool *isPlay, bool *isHighScore);

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
	// - ����ȭ������ ���ư� �� �־�� ��
	// - ������ �ٽ� ������ �� �־�� ��
	// +) Maybe : ��ŷ
}

bool ResultScreen(bool *isHighScore, bool *isPlay, int *saveScore, int *checkPlay)
{
	FILE *openFp = NULL;
	int inputNum = 0;
	printf("AnyKey\n\n");
	system("cls");

	if (*isHighScore == TRUE)
	{
		*saveScore = abs(*saveScore);
		fopen_s(&openFp, "HighestScore.dat", "wb");
		if (openFp == NULL)
		{
			puts("FileError!");
			return FALSE;
		}
		fwrite(saveScore, sizeof(int), 1, openFp);	// ���̳ʸ� ������ fwrite�� �����!
		fclose(openFp);

		printf("\n\n                 [ RESULT ]\n\n\n");
		printf("\n>> Congratulations!\n>> You get a New High Score\n\n Score : %d\n\n", *saveScore);
	}
	else
	{
		system("cls");
		printf("\n\n                 [ RESULT ]\n\n\n");
		printf("\n>> You're Score\n\nscore : %d\n\n", *saveScore);
	}

	printf("\n\n\n\n>> Select Menu\n\n[ OPTION ]\n- Go to Main, Push '1'\n- Start New Game, Push '2'\n- Exit Game, Push 'AnyKey'\n\nInput : ");
	
	inputNum = _getch();
	if (inputNum == inputNum_1)	// ����ȭ��
	{
		puts("1");
		*checkPlay = mainScene;
		*isPlay = TRUE;
	}
	else if (inputNum == inputNum_2)	// ����ȭ��
	{
		*checkPlay = gameScene;
		*isPlay = TRUE;
	}
	else
	{
		puts("Exit");
		*checkPlay = gameExit;
		*isPlay = FALSE;
	}

	// ����ȭ�� or ����ȭ�� or ���� ���� �߰�
}

void SetValue(int *nowScore, int *saveScore, int *checkPlay, bool *isPlay, bool *isHighScore)
{
	*nowScore = 0;
	*saveScore = 0;
	*checkPlay = 0;
	*isPlay = TRUE;
	*isHighScore = TRUE;
}