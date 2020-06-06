#include "BasicHeader.h"
#include "GameScreenHeader.h"
#include "MainResultHeader.h"

int main()
{
	bool isPlay = TRUE;
	bool isHighScore = TRUE;
	int nowScore = 0;
	int highestScore = 0;
	int saveScore = 0;
	int checkPlay = startGame;

	srand((unsigned)time(NULL));
	system("mode con cols=44 lines=41");
	CursorView(0);

	// todo : 메인화면 및 튜토리얼
	// +) Maybe : BGM, 랭킹

	// todo : 게임 화면
	// +) Maybe : 장애물 생성 맵, 맵 크기 확장, 랭킹, 이동 O,X 시 효과음

	while (1)
	{
		if (checkPlay == gameExit)
			break;

		if (checkPlay == mainScene)
		{
			MainScreen(&checkPlay);
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

	// todo : 게임 종료 화면
	// +) Maybe : 랭킹
}
