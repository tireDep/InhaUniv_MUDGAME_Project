#include "BasicHeader.h"
#include "GameScreenHeader.h"

int main()
{
	int checkPlay = 0;
	srand((unsigned)time(NULL));
	system("mode con cols=39 lines=39");

	// todo/Maybe : bgm �߰�, ��ֹ� or �� ũ�� Ȯ��
	// todo : ����ȭ�� �� Ʃ�丮��

	// todo
	// - ���� �� �ִ� �ְ� ������ ��, ���� ����
	// - ���� ���, �ְ��� ���
	
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

	// todo : ���� ��� �� ���ھ// ����
}
