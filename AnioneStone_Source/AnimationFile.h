#pragma once

#include "stdafx.h"

typedef struct ANIFILEHEADERtag
{
	BYTE       Symbol[4];           // "ANIM"						
    int        nFrameCount;         // ��������Ʈ ������ ����
} ANIFILEHEADER;

BOOL __afSave(SLMEMBER* pslm, char* pstrFilename);
BOOL __afLoad(SLMEMBER* pslm, char* pstrFilename); 
BOOL __afLoad2MemDc(SLMEMBER* pslm, char* pstrFilename, HDC hdc); 
