#include "stdafx.h"

SURFACEINFO __sy_sfBG;	// ǥ��
int __sy_nY;
int __sy_nHeight;
int __sy_nDist;			// ��ũ�ѵ� �Ÿ�
extern char * g_cScene;

void __syInit(HDC hdc, int nHeight)
{
	////
	__sy_nHeight = nHeight;
	__sy_nDist = 0;
	__sy_nY = -__sy_sfBG.nHeight+__sy_nHeight;

	////

	if (!strcmp(g_cScene, "����"))
	{
		__geSetImgSurface(&__sy_sfBG);
		__sy_sfBG.hBmp = __geBmpFile2BmpHandle(".\\Data\\DOS\\background.bmp");
		__geLoadSurface(hdc, &__sy_sfBG);
	}

	if (!strcmp(g_cScene,"�Ѱ���"))
	{
		__geSetImgSurface(&__sy_sfBG);
		__sy_sfBG.hBmp = __geBmpFile2BmpHandle(".\\Data\\DOS\\�Ѱ���.bmp");
		__geLoadSurface(hdc, &__sy_sfBG);
	}
}

void __syRelease()
{
	__geReleaseSurface(&__sy_sfBG);
}

void __syHScroll(int nStepY)
{
}

int	__syGetDist()
{
	return __sy_nDist;
}

void __syResetDist()
{
	__sy_nDist = 0;
}

void __syPutScenery(HDC hdc)
{	
	__gePutImage(hdc, 0, 0, &__sy_sfBG);
}

void __syChangeBackGround(HDC hdc, char *file)
{
}
