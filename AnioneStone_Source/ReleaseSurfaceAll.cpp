#include "stdafx.h"

void __ReleaseSurfaceAll(SLMEMBER* pslm)
{
	//// �޸�DC ����Ʈ
	SURFACEINFO* psInfo;
	__slSetMember(pslm);
	__slSetHeadPosition();	// �ݵ�� ������������� ����!
	while(psInfo = (SURFACEINFO*) __slGetNext())
	{		
		__geReleaseSurface(psInfo);
		free(psInfo);		
		psInfo = 0;
	}
	__slRemoveAll();
	__slInitMember(pslm);
}
