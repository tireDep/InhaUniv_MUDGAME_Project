#include "BasicHeader.h"
#include "GameScreenHeader.h"

bool ResultScreen(bool *isHighScore, bool *isPlay, int *saveScore, int *checkPlay);

int main()
{
	int saveScore = 0;
	int checkPlay = 0;
	bool isPlay = TRUE;
	bool isHighScore = TRUE;

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
	
	Update(&checkPlay, &saveScore);
	while (checkPlay >= 0)
	{
		if (checkPlay == 50)
		{
			printf("2\n\n>> ReStart Game\n\nReady to New Game : ");
			for (int i = 5; i > 0; i--)
			{
				Sleep(100);
				printf("%d ", i);
			}
			checkPlay = 0;
			Update(&checkPlay, &saveScore);
		}
		else
		{
			if (saveScore < 0)
			{
				printf("AnyKey\n\n");
				
				// ---------------------------------
				isHighScore = TRUE;
				ResultScreen(&isHighScore, &isPlay, &saveScore, &checkPlay);
				if (!isPlay)
					break;
				else
					continue;
			}
			else
			{
				printf("AnyKey\n\n");

				// ---------------------------------

				isHighScore = FALSE;
				ResultScreen(&isHighScore, &isPlay, &saveScore, &checkPlay);
				if (!isPlay)
					break;
				else
					continue;
			}
		}
	}

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
		fwrite(&saveScore, sizeof(int), 1, openFp);	// ���̳ʸ� ������ fwrite�� �����!
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

	printf("\n\n\n\n>> Select Menu\n\n[ OPTION ]\n- Go to Main, Push '1'\n- Start Another Game, Push '2'\n- Exit Game, Push 'AnyKey'\n\nInput : ");
	
	inputNum = _getch();
	if (inputNum == 49)	// ����ȭ�� // ���� �̱���
	{
		puts("1");
		//*checkPlay = 100;
		//*isPlay = TRUE;
		*isPlay = FALSE;
	}
	else if (inputNum == 50)	// ����ȭ��
	{
		*isPlay = TRUE;
		*checkPlay = 50;
	}
	else
	{
		puts("Exit");
		*isPlay = FALSE;
	}

	// ����ȭ�� or ����ȭ�� or ���� ���� �߰�
}