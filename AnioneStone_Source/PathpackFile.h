#pragma once

#include "stdafx.h"

typedef struct PATHFILEHEADERtag
{
	BYTE       Symbol[4];      // "PATH"
    int        nResolution;    // ��� ���� ���� ����
} PATHFILEHEADER;

BOOL __ppSave(char* pstrFilename);
BOOL __ppLoad(DAMEMBER* pdamPath, char* pstrFilename);

