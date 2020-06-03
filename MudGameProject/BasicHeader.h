#pragma once

#include<stdio.h>
#include<conio.h>	// _getch()
#include<time.h>
#include<stdlib.h>
#include<Windows.h>

#define BASICARRSIZE 4
#define MAXNUM 131072 
// 3*3 = 1,024 / 4*4 = 131,072 / 5*5 = 67,108,864(65,536) / 6*6 이상은 숫자가 너무 큼
enum MovePos { stayMove = 0, rightMove = 1, leftMove = -1, upMove = -1, downMove = 1 };
enum NextPos { setZero = 0, setArrSize = BASICARRSIZE, plusPos = 1, minusPos = -1 };


#define BLACK 0 
// #define BLUE 1 
// #define GREEN 2 
// #define CYAN 3 
// #define RED 4 
// #define MAGENTA 5 
// #define BROWN 6 
// #define LIGHTGRAY 7 
// #define DARKGRAY 8 
// #define LIGHTBLUE 9 
// #define LIGHTGREEN 10 
// #define LIGHTCYAN 11 
// #define LIGHTRED 12 
// #define LIGHTMAGENTA 13 
// #define YELLOW 14 
#define WHITE 15

#include<math.h>