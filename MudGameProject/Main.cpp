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
	// - 점수 계산, 최고점 계산
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

				system("cls");
				saveScore = abs(saveScore);

				fopen_s(&openFp, "HighestScore.dat", "wb");
				if (openFp == NULL)
				{
					puts("FileError!");
					return 0;
				}
				fwrite(&saveScore, sizeof(int), 1, openFp);	// 바이너리 파일은 fwrite로 써야함!
				fclose(openFp);

				printf("\n\n                [ RESULT ]\n\n");
				printf("\n>> Congratulations!\n>> You get a New High Score\n\n Score : %d\n\n", saveScore);

				// 시작화면 or 게임화면 or 종료 조건 추가
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
				fwrite(&saveScore, sizeof(int), 1, openFp);	// 바이너리 파일은 fwrite로 써야함!
				fclose(openFp);
				*/
				printf("\n\n                [ RESULT ]\n\n");
				printf("\n>> You're Score\n\nscore : %d\n\n", saveScore);
				// 시작화면 or 게임화면 or 종료 조건 추가
			}
			puts(">> Game Exit\n");
			_getch();	// 릴리즈시 바로꺼짐 해결_1
			//system("pause > nul");	// 릴리즈시 바로꺼짐 해결_2
			return 0;
		}
	}

	// todo : 게임 종료 화면
	// - 결과 보여주기(획득 점수, 최고점일 경우 New High Score 추가해서 출력) : 점수 계산
	// - 시작화면으로 돌아갈 수 있어야 함
	// - 게임을 다시 시작할 수 있어야 함
	// +) Maybe : 랭킹
}
