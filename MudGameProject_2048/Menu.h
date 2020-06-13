#pragma once

#include "BasicHeader.h"

void GotoXY(int x, int y);
void TextColor(int foreground, int background);
BYTE SelectMenu(BYTE initX, BYTE initY, BYTE gap, BYTE maxMenu, BYTE menuString[][20]);
void EraseMenu(BYTE initX, BYTE initY, BYTE gap, BYTE maxMenu, BYTE menuString[][20]);