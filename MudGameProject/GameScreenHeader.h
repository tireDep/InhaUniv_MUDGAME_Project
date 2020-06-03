#pragma once

void SetStartMap(int(*mapArr)[BASICARRSIZE], int check);
void PlayerInput(int(*mapArr)[BASICARRSIZE], int *checkCanMove);

void MoveToInput(int(*mapArr)[BASICARRSIZE], int *posY, int *posX, int moveY, int moveX, int setStart, int setNext, int moveTo);

void SetAbsVal_UpDown(int(*mapArr)[BASICARRSIZE], int posX);
void SetAbsVal_RightLeft(int(*mapArr)[BASICARRSIZE], int posY);

void PrintArr(int(*mapArr)[BASICARRSIZE], char *string);
void TextColor(int foreground, int background);