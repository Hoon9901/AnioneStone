#pragma once

#include "stdafx.h"

void __syInit(HDC hdc, int nHeight);
void __syRelease();
void __syHScroll(int nStepY);
void __syResetDist();
int	 __syGetDist();
void __syPutScenery(HDC hdc);
void __syChangeBackGround(HDC hdc, char *file);

