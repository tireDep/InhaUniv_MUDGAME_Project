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

	// todo : 메인화면 및 튜토리얼
	// - 게임 시작
	// - 튜토리얼
	// - 게임 종료
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
	// - 입력키, 일시정지키
	// - 메인화면(뒤로가기)

	// todo : 게임 화면
	// +) Maybe : 장애물 생성 맵, 맵 크기 확장, 랭킹, 이동 O,X 시 효과음

	while (1)
	{
		if (checkPlay == gameExit)
			break;
	
		else if (checkPlay == mainScene)
		{
			// 메인화면 구현
			system("cls");
			puts("------------------메인화면 구현해야함-----------");
			Sleep(500);
			
			checkPlay = gameScene;	// 게임시작 선택시
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

	// todo : 게임 종료 화면
	// +) Maybe : 랭킹
}
