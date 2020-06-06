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

	// todo : 메인화면 및 튜토리얼
	// +) Maybe : BGM, 랭킹

	// todo : 튜토리얼
	// - text 형태로 플레이 방법 출력
	// - 플레이 방법
	/*
	--> 방향키를 입력해서 숫자블록을 이동시킬 수 있음(상하좌우)
	□↑□
	←2→
	□↓□

	--> 같은 숫자블록을 만날 경우, 숫자 블록은 합쳐짐
	□2□2 => □□2+2 => □□□4

	--> 더 이상 움직일 수 없거나,((?)최고 숫자를 만들 경우) 게임 종료

	*/

	// todo : 게임 화면
	// +) Maybe : 장애물 생성 맵, 맵 크기 확장, 랭킹, 이동 O,X 시 효과음

	while (1)
	{
		if (checkPlay == gameExit)
			break;

		if (checkPlay == mainScene)
		{
			// 메인화면
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
				checkPlay = gameScene;	// 게임시작 선택시

			else if (inputNum == inputNum_2)
			{
				// 튜토리얼
				system("cls");
				printf("\n\n                 [ TUTORIAL ]\n\n\n");
				// checkPlay = tutorialScene;
				
				printf(">> 게임설명\n\n");
				printf("- 같은 숫자블록을 합쳐\n  큰 숫자를 만드는 게임\n\n\n");

				printf(">> 게임방법\n\n");
				printf("- 방향키로             □↑□ \n");
				printf("  숫자블록을           ←②→ \n");
				printf("  이동시킬 수 있음     □↓□ \n");

				printf("\n- 같은 숫자블록이 만날 경우,\n  합쳐지면서 점수를 얻을 수 있음\n");
				printf("\n  → : □2□2 => □□2+2 => □□□4\n\n\n");

				printf(">> 입력키\n\n- 이동 : ↑, ↓, ←, →\n\n- 일시정지 : ESC\n\n\n");
				printf(">> 게임오버\n\n- 모든 칸에 숫자 블록이 있고,\n  해당 방향으로 이동할 수 없을 때\n\n\n");
				// printf("\n- 주어진 맵에서 만들 수 있는\n  가장 큰 숫자를 만들었을 때\n\n  4x4 기준 : 131,072\n\n\n");

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

	// todo : 게임 종료 화면
	// +) Maybe : 랭킹
}
