#include "BasicHeader.h"
#include "GameScreenHeader.h"

int main()
{
	int checkPlay = 0;
	srand((unsigned)time(NULL));
	system("mode con cols=39 lines=39");

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
	
	Update(&checkPlay);
	while (checkPlay >= 0)
	{
		if (checkPlay == 50)
		{
			printf("2\n\n>> ReStart Game\n\nReady to New Game : ");
			for (int i = 5; i > 0; i--)
			{
				Sleep(500);
				printf("%d ", i);
			}
			checkPlay = 0;
			Update(&checkPlay);
		}
		else
		{
			puts("AnyKey\n\n>> Game Exit\n");
			return 0;
		}
	}

	// todo : ���� ���� ȭ��
	// - ��� �����ֱ�(ȹ�� ����, �ְ����� ��� New High Score �߰��ؼ� ���) : ���� ���
	// - ����ȭ������ ���ư� �� �־�� ��
	// - ������ �ٽ� ������ �� �־�� ��
	// +) Maybe : ��ŷ
}
