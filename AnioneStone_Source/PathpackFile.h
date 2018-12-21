#pragma once

#include "stdafx.h"

typedef struct PATHFILEHEADERtag
{
	BYTE       Symbol[4];      // "PATH"
    int        nResolution;    // 경로 상의 점의 개수
} PATHFILEHEADER;

BOOL __ppSave(char* pstrFilename);
BOOL __ppLoad(DAMEMBER* pdamPath, char* pstrFilename);

