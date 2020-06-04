#include "BasicHeader.h"
#include "GameScreenHeader.h"

int main()
{
	int checkPlay = 0;
	srand((unsigned)time(NULL));
	system("mode con cols=39 lines=39");

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

	// todo : 게임 종료 화면
	// - 결과 보여주기(획득 점수, 최고점일 경우 New High Score 추가해서 출력) : 점수 계산
	// - 시작화면으로 돌아갈 수 있어야 함
	// - 게임을 다시 시작할 수 있어야 함
	// +) Maybe : 랭킹
}
