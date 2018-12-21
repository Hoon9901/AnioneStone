#include "stdafx.h"

void __ReleaseSurfaceAll(SLMEMBER* pslm)
{
	//// 메모리DC 리스트
	SURFACEINFO* psInfo;
	__slSetMember(pslm);
	__slSetHeadPosition();	// 반드시 헤드포지션으로 설정!
	while(psInfo = (SURFACEINFO*) __slGetNext())
	{		
		__geReleaseSurface(psInfo);
		free(psInfo);		
		psInfo = 0;
	}
	__slRemoveAll();
	__slInitMember(pslm);
}
