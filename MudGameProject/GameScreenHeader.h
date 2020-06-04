#pragma once

int Update(int *checkPlay);
void SetNewNum(int(*mapArr)[BASICARRSIZE], int check);
void PlayerInput(int(*mapArr)[BASICARRSIZE], int *checkCanMove, int *checkGameOver, int *checkMaxNum, int *kbhitCnt);

bool IsCanMove(int(*mapArr)[BASICARRSIZE], int posY, int posX, int *checkCanMove, int *checkGameOver, int *checkMaxNum, int moveY, int moveX);
void MoveToInput(int(*mapArr)[BASICARRSIZE], int *posY, int *posX, int moveY, int moveX, int setStart, int setNext, int moveTo);

void SetAbsVal_UpDown(int(*mapArr)[BASICARRSIZE], int posX);
void SetAbsVal_RightLeft(int(*mapArr)[BASICARRSIZE], int posY);

void PrintArr(int(*mapArr)[BASICARRSIZE], char *string, int *kbhitCnt);
void TextColor(int foreground, int background);

bool CheckGameContinue(int(*mapArr)[4], int *kbhitCnt, int *checkPlay);
void PrintNewInput(int(*mapArr)[4], char *string, int *kbhitCnt);

void DeleteInput(int *kbhitCnt);
void CheckKbhitCnt(int *kbhitCnt);

// int checkMaxNum = 0;