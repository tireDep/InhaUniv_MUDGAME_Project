#pragma once

void MainScreen(int *checkPlay, bool *isBgm, bool *isSoundEffect);
void TutorialScreen(int *checkPlay, int inputNum, bool *isSoundEffect);
void SoundOption(bool *isBgm, bool *isSoundEffect, int *checkPlay);

bool ResultScreen(bool *isHighScore, bool *isPlay, int *saveScore, int *checkPlay, bool isBlock, bool isSoundEffect, int blockCnt);