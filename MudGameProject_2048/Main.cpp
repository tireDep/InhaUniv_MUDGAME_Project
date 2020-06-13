#include "BasicHeader.h"
#include "GameScreen.h"
#include "StartResultScreen.h"
#include "Menu.h"

MCI_OPEN_PARMS m_mciOpenParms;
MCI_PLAY_PARMS m_mciPlayParms;
MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;
DWORD dwID = 0;

int main()
{
	bool isPlay = TRUE;
	bool isHighScore = TRUE;
	bool isBlock = TRUE;
	bool isContinue = FALSE;
	bool tempMode = TRUE;
	bool isBgm = TRUE;
	bool isSoundEffect = TRUE;

	int inputMode = 0;
	int nowScore = 0;
	int highestScore = 0;
	int saveScore = 0;
	int checkPlay = startGame;
	int blockCnt = 0;

	srand((unsigned)time(NULL));
	system("mode con cols=44 lines=47");
	system("title MUD_2048");
	CursorView(0);

	size_t cnt;
	char buffer[] = ".\\sound\\bgm.wav";
	wchar_t bgmName[30] = L"";
	mbstowcs_s(&cnt, bgmName, strlen(buffer) + 1, buffer, strlen(buffer) + 1);
	LPCWSTR lpcBgmName = bgmName;

	strcpy_s(buffer, "mpegvideo");
	wchar_t fileType[30] = L"";
	mbstowcs_s(&cnt, fileType, strlen(buffer) + 1, buffer, strlen(buffer) + 1);
	LPCWSTR lpcTypeName = fileType;

	mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
	mciOpen.lpstrElementName = lpcBgmName; // 파일 경로 입력
	mciOpen.lpstrDeviceType = lpcTypeName;

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
	dwID = mciOpen.wDeviceID;

	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_mciPlayParms);	// play & repeat
	// bgm

	while (1)
	{
		if (checkPlay == gameExit)
			break;

		if (checkPlay == mainScene)
		{
			StartScreen(&checkPlay, &isBgm, &isSoundEffect);
		}

		if (checkPlay == gameSelectScene)
		{
			if (isSoundEffect) sndPlaySoundA(".\\sound\\highUp.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
			if (!isContinue)
			{
				while (checkPlay == gameSelectScene)
					CheckBlockMode(&inputMode, &isBlock, &isSoundEffect, &checkPlay, &blockCnt);
				if (checkPlay == mainScene)
				{
					continue;
				}
				tempMode = isBlock;
			}
			else
			{
				isBlock = tempMode;
			}

			
		}
		

		if (checkPlay == gameScene)
		{
			SetValue(&nowScore, &highestScore, &saveScore, &checkPlay, &inputMode, &isPlay, &isHighScore, &isBlock);
			Start(&highestScore, isBlock, blockCnt);
			Update(&checkPlay, &saveScore, &nowScore, &highestScore, blockCnt, isBlock, &isBgm, &isSoundEffect);
			isContinue = TRUE;

			if (checkPlay == gameScene)	// ★ : 이거 없으면 게임 종료할때도 카운트 다운 실행됨..
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
			isContinue = FALSE;

			if (saveScore < 0)
			{
				isHighScore = TRUE;
				ResultScreen(&isHighScore, &isPlay, &saveScore, &checkPlay, isBlock, isSoundEffect, blockCnt);
				if (!isPlay)
					break;
				else
					continue;
			}
			else
			{
				isHighScore = FALSE;
				ResultScreen(&isHighScore, &isPlay, &saveScore, &checkPlay, isBlock, isSoundEffect, blockCnt);
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
}
