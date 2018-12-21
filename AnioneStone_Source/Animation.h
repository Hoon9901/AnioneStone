#pragma once

#include "stdafx.h"

void __anReset(SLMEMBER* pslmMember);
RECT __anGetCurSprRect(ANIINFO* pAi);	
BOOL __anAnimateOnce(HDC hdc, int nX, int nY, ANIINFO* pAi);
void __anAnimate(HDC hdc, int nX, int nY, ANIINFO* pAi);

