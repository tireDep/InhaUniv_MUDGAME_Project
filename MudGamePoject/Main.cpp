#include "BasicHeader.h"
#include "GameScreenHeader.h"
#include "MainResultHeader.h"

MCI_OPEN_PARMS m_mciOpenParms;
MCI_PLAY_PARMS m_mciPlayParms;
DWORD m_dwDeviceID;
MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;

int dwID;

int main()
{
	/*mciOpen.lpstrElementName = ".\\sound\\bgm2.mp3"; // 파일 경로 입력
	mciOpen.lpstrDeviceType = "mpegvideo";
	// 밑줄 뜰 경우, 프로젝트 -> (가장 아래있는)속성 -> 구성속성 -> 문자 집합 -> 설정 안함

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)&mciOpen);

	dwID = mciOpen.wDeviceID;

	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, // play & repeat
		(DWORD)(LPVOID)&m_mciPlayParms);*/


	/* mciSendCommandW(dwID, MCI_PAUSE, MCI_NOTIFY,
	(DWORD)(LPVOID)&m_mciPlayParms); */// Pause

	/* mciSendCommandW(dwID, MCI_RESUME, 0, NULL); */// resume

   /* mciSendCommandW(dwID, MCI_CLOSE, 0, NULL); */// stop


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
	CursorView(0);

	// todo : 메인화면 및 튜토리얼
	// +) Maybe : 랭킹

	// todo : 게임 화면
	// +) Maybe : 맵 크기 확장, 랭킹


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

	while (1)
	{
		if (checkPlay == gameExit)
			break;

		if (checkPlay == mainScene)
		{
			MainScreen(&checkPlay, &isBgm, &isSoundEffect);
		}

		if (checkPlay == gameScene)
		{
			if (isSoundEffect) sndPlaySoundA(".\\sound\\highUp.wav", SND_ASYNC | SND_NODEFAULT);	// soundEffect
			SetValue(&nowScore, &highestScore, &saveScore, &checkPlay, &inputMode, &isPlay, &isHighScore, &isBlock);
			if (!isContinue)
			{
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

			Start(&highestScore, isBlock);
			Update(&checkPlay, &saveScore, &nowScore, &highestScore, blockCnt, isBlock, &isBgm, &isSoundEffect);

			if (checkPlay == gameScene)
			{
				isContinue = TRUE;
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
				ResultScreen(&isHighScore, &isPlay, &saveScore, &checkPlay, isBlock, isSoundEffect);
				if (!isPlay)
					break;
				else
					continue;
			}
			else
			{
				isHighScore = FALSE;
				ResultScreen(&isHighScore, &isPlay, &saveScore, &checkPlay, isBlock, isSoundEffect);
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
