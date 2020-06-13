#pragma once

// #include "BasicHeader.h"

void SetValue(int *nowScore, int *highestScore, int *saveScore, int *checkPlay, int *inputMode, bool *isPlay, bool *isHighScore, bool *isBlock);
void SetNewNum(int(*mapArr)[BASICARRSIZE], int check);
void SetBlock(int(*mapArr)[BASICARRSIZE], int blockCnt);
void SetAbsVal_UpDown(int(*mapArr)[BASICARRSIZE], int posX);
void SetAbsVal_RightLeft(int(*mapArr)[BASICARRSIZE], int posY);

void CheckBlockMode(int *inputMode, bool *isBlock, bool *isSoundEffect, int *checkPlay, int *blockCnt);
bool CheckGameContinue(int(*mapArr)[4], int *kbhitCnt, int *checkPlay, bool *isBgm, bool *isSoundEffect);
void CheckHighScore(int *nowScore, int *highestScore, int prevScore, int *saveScore, int *checkPlay, int sceneNum);
void CheckSaveHighScore(int *checkPlay, int *highestScore, int *saveScore);
void DeleteInput(int *kbhitCnt);
void CheckKbhitCnt(int *kbhitCnt);

int Start(int *highestScore, bool isBlock, int blockCnt);
int Update(int *checkPlay, int *saveScore, int *nowScore, int *highestScore, int blockCnt, bool isBlock, bool *isBgm, bool *isSoundEffect);
void PlayerInput(int(*mapArr)[BASICARRSIZE], int *checkCanMove, int *checkGameOver, int *checkMaxNum, int *kbhitCnt, int *nowScore, int *highestScore);
bool IsCanMove(int(*mapArr)[BASICARRSIZE], int posY, int posX, int *checkCanMove, int *checkGameOver, int *checkMaxNum, int moveY, int moveX);
void MoveToInput(int(*mapArr)[BASICARRSIZE], int *posY, int *posX, int moveY, int moveX, int setStart, int setNext, int moveTo, int *nowScore, int *highestScore);

void PrintArr(int(*mapArr)[BASICARRSIZE], char *string, int *kbhitCnt, int *nowScore, int *highestScore);
void PrintNewInput(int(*mapArr)[4], char *string, int *kbhitCnt, int *nowScore, int *highestScore);
void CursorView(char show);
void ClearScreen_ReStart();

extern MCI_OPEN_PARMS m_mciOpenParms;
extern MCI_PLAY_PARMS m_mciPlayParms;
extern MCI_OPEN_PARMS mciOpen;
extern MCI_PLAY_PARMS mciPlay;
extern DWORD dwID;
// BGM, Sound Effect