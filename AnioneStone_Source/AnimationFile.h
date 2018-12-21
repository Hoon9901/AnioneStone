#pragma once

#include "stdafx.h"

typedef struct ANIFILEHEADERtag
{
	BYTE       Symbol[4];           // "ANIM"						
    int        nFrameCount;         // 스프라이트 프레임 개수
} ANIFILEHEADER;

BOOL __afSave(SLMEMBER* pslm, char* pstrFilename);
BOOL __afLoad(SLMEMBER* pslm, char* pstrFilename); 
BOOL __afLoad2MemDc(SLMEMBER* pslm, char* pstrFilename, HDC hdc); 
