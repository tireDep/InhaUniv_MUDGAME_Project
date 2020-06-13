#include "BasicHeader.h"
#include "StartResultScreen.h"
#include "Menu.h"

void StartScreen(int *checkPlay, bool *isBgm, bool *isSoundEffect)
{
	int inputNum = 0;
	int curMenu = -1;

	BYTE menuGap = 3;
	BYTE baseX = 14;
	BYTE baseY = 20;
	BYTE maxMenu = 4;
	BYTE menuString[4][20] =
	{
		" 1. Game Start   ",
		" 2. Tutorial     ",
		" 3. Sound Option ",
		" 4. Exit         ",
	};
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n");
	printf("         ___     ___     ___     ___  \n");
	printf("       || 2 |  || 0 |  || 4 |  || 8 | \n");
	printf("       ||___|  ||___|  ||___|  ||___| \n");
	printf("       |/___|  |/___|  |/___|  |/___| \n");
	printf("\n\n\n\n\n\n\n");

	printf("             [ 1. Game Start   ]\n\n\n");
	printf("             [ 2. Tutorial     ]\n\n\n");
	printf("             [ 3. Sound Option ]\n\n\n");
	printf("             [ 4. Exit         ]\n\n\n\n\n\n");

	inputNum = SelectMenu(baseX, baseY, menuGap, maxMenu, menuString);

	if (*isSoundEffect) sndPlaySoundA(".\\sound\\highUp.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
	if (inputNum == inputNum_1)
		*checkPlay = gameSelectScene;	// 게임시작 선택시

	else if (inputNum == inputNum_2)
		TutorialScreen(checkPlay, inputNum, isSoundEffect);

	else if (inputNum == inputNum_3)
		SoundOption(isBgm, isSoundEffect, checkPlay);

	else if (inputNum == inputNum_4)
	{
		if (*isSoundEffect) sndPlaySoundA(".\\sound\\highDown.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
		*checkPlay = gameExit;
	}

}

void TutorialScreen(int *checkPlay, int inputNum, bool *isSoundEffect)
{
	if (*isSoundEffect) sndPlaySoundA(".\\sound\\highUp.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
	system("cls");
	printf("\n\n                 [ TUTORIAL ]\n\n\n");

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
	printf("    [ Input AnyKey, You Can Go To Main ]\n");

	inputNum = _getch();
	if (inputNum != NULL)
		*checkPlay = mainScene;

	if (*isSoundEffect) sndPlaySoundA(".\\sound\\highDown.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
}

void SoundOption(bool *isBgm, bool *isSoundEffect, int *checkPlay)
{
	if (*isSoundEffect) sndPlaySoundA(".\\sound\\highUp.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
	int inputNum = 0;
	while (1)
	{
		Sleep(250);
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("              [ Sound Option ]\n\n\n\n");
		printf("    >> Bgm On / Off, push '1'\n\n\n");
		printf("    >> SoundEffect On / Off, push '2'\n\n\n");
		printf("    >> Go to Main, push 'AnyKey'\n\n");

		inputNum = _getch();
		if (inputNum == inputNum_1)
		{
			if (*isBgm)
			{
				printf("\n\n                 [ BGM OFF ]\n\n");
				mciSendCommandW(dwID, MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)&m_mciPlayParms);
				*isBgm = FALSE;
			}
			else
			{
				printf("\n\n                 [ BGM ON ]\n\n");
				mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_mciPlayParms);
				*isBgm = TRUE;
			}
		}
		else if (inputNum == inputNum_2)
		{
			if (*isSoundEffect)
			{
				printf("\n\n           [ Sound Effect OFF ]\n\n");
				*isSoundEffect = FALSE;
			}
			else
			{
				printf("\n\n           [ Sound Effect ON ]\n\n");
				*isSoundEffect = TRUE;
			}
		}
		else
		{
			if (*isSoundEffect) sndPlaySoundA(".\\sound\\highDown.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
			*checkPlay = mainScene;
			return;
		}
	}
}
