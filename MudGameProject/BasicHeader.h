#pragma once

#include<stdio.h>
#include<conio.h>	// _getch()
#include<time.h>
#include<stdlib.h>
#include<Windows.h>
#include<math.h>

#define BLACK 0 
#define WHITE 15
#define BASICARRSIZE 4
#define MAXNUM 131072 
// 3*3 = 1,024 / 4*4 = 131,072 / 5*5 = 67,108,864(65,536) / 6*6 이상은 숫자가 너무 큼

enum MovePos { stayMove = 0, rightMove = 1, leftMove = -1, upMove = -1, downMove = 1 };
enum NextPos { zeroPos = 0, arrSizePos = BASICARRSIZE, plusPos = 1, minusPos = -1 };
enum CheckPos { upDownPos = 0, leftRightPos = 1 };
