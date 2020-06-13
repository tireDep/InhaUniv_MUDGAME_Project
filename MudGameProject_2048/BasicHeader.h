#pragma once

#include<stdio.h>
#include<conio.h>	// _getch()
#include<time.h>
#include<stdlib.h>
#include<Windows.h>
#include<math.h>
#include<io.h>	// _access()

#include<Digitalv.h>
#include<mmsyscom.h>
#pragma comment(lib, "winmm.lib")
// bgm, soundEffect

#define BLACK 0 
#define WHITE 15
#define BASICARRSIZE 4
#define BASICARR_MAXNUM 131072 
// 3*3 = 1,024 / 4*4 = 131,072 / 5*5 = 67,108,864(65,536) / 6*6 이상은 숫자가 너무 큼

enum MovePos { stayMove = 0, rightMove = 1, leftMove = -1, upMove = -1, downMove = 1 };
enum NextPos { zeroPos = 0, arrSizePos = BASICARRSIZE, plusPos = 1, minusPos = -1 };
enum CheckPos { upDownPos = 0, leftRightPos = 1 };
enum CheckScene
{
	mainScene = 0, gameSelectScene = 49, gameScene = 50, resultScene = 100, optionScene = 101, gameExit = -9999, startGame = 0,
	inputNum_1 = 49, inputNum_2 = 50, inputNum_3 = 51, inputNum_4 = 52, inputBtn_Esc = 27,
	arrowStart = 224, arrowUp = 72, arrowDown = 80, arrowLeft = 75, arrowRight = 77,
	enter = 13, spaceBar = 32
};
