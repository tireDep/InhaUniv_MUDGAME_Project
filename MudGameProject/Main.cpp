#include "BasicHeader.h"
#include "GameScreenHeader.h"

int main()
{
	FILE *openFp = NULL;
	int saveScore = 0;
	int checkPlay = 0;

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
	// - ���� ���, �ְ��� ���
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

				system("cls");
				saveScore = abs(saveScore);

				fopen_s(&openFp, "HighestScore.dat", "wb");
				if (openFp == NULL)
				{
					puts("FileError!");
					return 0;
				}
				fwrite(&saveScore, sizeof(int), 1, openFp);	// ���̳ʸ� ������ fwrite�� �����!
				fclose(openFp);

				printf("\n\n                [ RESULT ]\n\n");
				printf("\n>> Congratulations!\n>> You get a New High Score\n\n Score : %d\n\n", saveScore);

				// ����ȭ�� or ����ȭ�� or ���� ���� �߰�
			}
			else
			{
				printf("AnyKey\n\n");

				// ---------------------------------

				system("cls");

				/*
				fopen_s(&openFp, "HighestScore.dat", "wb");
				if (openFp == NULL)
				{
					puts("FileError!");
					return 0;
				}
				fwrite(&saveScore, sizeof(int), 1, openFp);	// ���̳ʸ� ������ fwrite�� �����!
				fclose(openFp);
				*/
				printf("\n\n                [ RESULT ]\n\n");
				printf("\n>> You're Score\n\nscore : %d\n\n", saveScore);
				// ����ȭ�� or ����ȭ�� or ���� ���� �߰�
			}
			puts(">> Game Exit\n");
			_getch();	// ������� �ٷβ��� �ذ�_1
			//system("pause > nul");	// ������� �ٷβ��� �ذ�_2
			return 0;
		}
	}

	// todo : ���� ���� ȭ��
	// - ��� �����ֱ�(ȹ�� ����, �ְ����� ��� New High Score �߰��ؼ� ���) : ���� ���
	// - ����ȭ������ ���ư� �� �־�� ��
	// - ������ �ٽ� ������ �� �־�� ��
	// +) Maybe : ��ŷ
}
