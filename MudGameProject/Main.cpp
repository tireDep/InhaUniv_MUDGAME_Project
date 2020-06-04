#include "BasicHeader.h"
#include "GameScreenHeader.h"

int main()
{
	srand((unsigned)time(NULL));
	system("mode con cols=39 lines=37");

	// todo/Maybe : bgm 추가, 장애물 or 맵 크기 확장
	// todo : 메인화면 및 튜토리얼

	// todo
	// - 만들 수 있는 최고 숫자일 때, 게임 종료
	// - 점수 계산, 최고점 계산
	Update();

	// todo : 점수 계산 및 스코어링// 미정
}
