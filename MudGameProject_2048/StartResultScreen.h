#pragma once

// #include "BasicHeader.h"

void StartScreen(int *checkPlay, bool *isBgm, bool *isSoundEffect);
void TutorialScreen(int *checkPlay, int inputNum, bool *isSoundEffect);
void SoundOption(bool *isBgm, bool *isSoundEffect, int *checkPlay);

bool ResultScreen(bool *isHighScore, bool *isPlay, int *saveScore, int *checkPlay, bool isBlock, bool isSoundEffect, int blockCnt);

extern MCI_OPEN_PARMS m_mciOpenParms;
extern MCI_PLAY_PARMS m_mciPlayParms;
extern MCI_OPEN_PARMS mciOpen;
extern MCI_PLAY_PARMS mciPlay;
extern DWORD dwID;
// BGM, Sound Effect