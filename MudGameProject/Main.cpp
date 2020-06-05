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
	// todo : 게임 종료 화면
	// - 시작화면으로 돌아갈 수 있어야 함
	// - 게임을 다시 시작할 수 있어야 함
	// +) Maybe : 랭킹
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
		fwrite(&saveScore, sizeof(int), 1, openFp);	// 바이너리 파일은 fwrite로 써야함!
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
	if (inputNum == 49)	// 메인화면 // 아직 미구현
	{
		puts("1");
		//*checkPlay = 100;
		//*isPlay = TRUE;
		*isPlay = FALSE;
	}
	else if (inputNum == 50)	// 게임화면
	{
		*isPlay = TRUE;
		*checkPlay = 50;
	}
	else
	{
		puts("Exit");
		*isPlay = FALSE;
	}

	// 시작화면 or 게임화면 or 종료 조건 추가
}