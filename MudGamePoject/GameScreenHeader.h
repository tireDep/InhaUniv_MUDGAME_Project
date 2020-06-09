#pragma once

#include "BasicHeader.h"	// BASICARRSIZE

void SetValue(int *nowScore, int *highestScore, int *saveScore, int *checkPlay, int *inputMode, bool *isPlay, bool *isHighScore, bool *isBlock);
int Start(int *highestScore, bool isBlock, int blockCnt);

void SetBlock(int(*mapArr)[BASICARRSIZE], int blockCnt);
void CheckBlockMode(int *inputMode, bool *isBlock, bool *isSoundEffect, int *checkPlay, int *blockCnt);

int Update(int *checkPlay, int *saveScore, int *nowScore, int *highestScore, int blockCnt, bool isBlock, bool *isBgm, bool *isSoundEffect);

void SetNewNum(int(*mapArr)[BASICARRSIZE], int check);
void PlayerInput(int(*mapArr)[BASICARRSIZE], int *checkCanMove, int *checkGameOver, int *checkMaxNum, int *kbhitCnt, int *nowScore, int *highestScore);

bool IsCanMove(int(*mapArr)[BASICARRSIZE], int posY, int posX, int *checkCanMove, int *checkGameOver, int *checkMaxNum, int moveY, int moveX);
void MoveToInput(int(*mapArr)[BASICARRSIZE], int *posY, int *posX, int moveY, int moveX, int setStart, int setNext, int moveTo, int *nowScore, int *highestScore);

void SetAbsVal_UpDown(int(*mapArr)[BASICARRSIZE], int posX);
void SetAbsVal_RightLeft(int(*mapArr)[BASICARRSIZE], int posY);

void PrintArr(int(*mapArr)[BASICARRSIZE], char *string, int *kbhitCnt, int *nowScore, int *highestScore);
void TextColor(int foreground, int background);

bool CheckGameContinue(int(*mapArr)[4], int *kbhitCnt, int *checkPlay, bool *isBgm, bool *isSoundEffect);
void PrintNewInput(int(*mapArr)[4], char *string, int *kbhitCnt, int *nowScore, int *highestScore);

void DeleteInput(int *kbhitCnt);
void CheckKbhitCnt(int *kbhitCnt);

void CursorView(char show);
