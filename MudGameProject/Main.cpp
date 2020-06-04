#include "BasicHeader.h"
#include "GameScreenHeader.h"

int main()
{
	int checkPlay = 0;
	srand((unsigned)time(NULL));
	system("mode con cols=39 lines=39");

	// todo/Maybe : bgm 추가, 장애물 or 맵 크기 확장
	// todo : 메인화면 및 튜토리얼

	// todo
	// - 만들 수 있는 최고 숫자일 때, 게임 종료
	// - 점수 계산, 최고점 계산
	
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

	// todo : 점수 계산 및 스코어링// 미정
}
