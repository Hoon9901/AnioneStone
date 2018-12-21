#include "stdafx.h"

SURFACEINFO* __an_psInfo=0;	// ���� ��� �ƴ�
DWORD __an_dwThisTick=0;	// ���� ��� �ƴ�

void __anReset(SLMEMBER* pslmMember)
{	
	__slSetMember(pslmMember);
	__slSetHeadPosition();
	__slGetMember(pslmMember);
}

//// ���� �ִϸ��̼� �ǰ� �ִ� ��������Ʈ�� �簢���� ����
RECT __anGetCurSprRect(ANIINFO* pAi)
{
	RECT rcSpr =  {0,0,0,0};
	__slSetMember(&(pAi->slAnimation));
	__an_psInfo = (SURFACEINFO*)__slGetAt();
	// ��尡 �ʱ�ȭ�� �ȵǾ��ų� ����� ���̸� ����
	if (!__an_psInfo) return rcSpr;
	__slGetMember(&(pAi->slAnimation));	// �ǹ� ����
	SetRect(&rcSpr, 0, 0, __an_psInfo->nWidth, __an_psInfo->nHeight);
	OffsetRect(&rcSpr, -__an_psInfo->nCentralX, -__an_psInfo->nCentralY);
	return rcSpr;	
}

//// �ѹ��� �ݺ�
BOOL __anAnimateOnce(HDC hdc, int nX, int nY, ANIINFO* pAi)
{    
	__slSetMember(&(pAi->slAnimation));

	//// ���� ǥ�������� ��´�
	__an_psInfo = (SURFACEINFO*)__slGetAt();

	// ��尡 �ʱ�ȭ�� �ȵǾ��ų� ����� ���̸� ����
	if (!__an_psInfo) return FALSE;
	
	//// ��������Ʈ �������� �����ð��� �Ѿ����?
	__an_dwThisTick = GetTickCount();	
	if (__an_dwThisTick - pAi->dwLastTick > __an_psInfo->dwDelayTime)
	{
		// ��������Ʈ ������ ����
		__an_psInfo = (SURFACEINFO*)__slGetNext();			
		pAi->dwLastTick = __an_dwThisTick;			
	}

	__slGetMember(&(pAi->slAnimation));	

	__gePutSprite(hdc, nX-__an_psInfo->nCentralX, nY-__an_psInfo->nCentralY, __an_psInfo , RGB(255,255,255));

	return TRUE;
}

//// ���� �ݺ�
void __anAnimate(HDC hdc, int nX, int nY, ANIINFO* pAi)
{    
	__slSetMember(&(pAi->slAnimation));

	//// ���� ǥ�������� ��´�
	__an_psInfo = (SURFACEINFO*)__slGetAt();

	// ��尡 �ʱ�ȭ�� �ȵǾ��ų� ����� ���̸� ����
	if (!__an_psInfo) 
	{				
		__slSetHeadPosition();
		__an_psInfo = (SURFACEINFO*)__slGetAt();
		if (!__an_psInfo) return;
	}
	
	//// ��������Ʈ �������� �����ð��� �Ѿ����?
	__an_dwThisTick = GetTickCount();	
	if (__an_dwThisTick - pAi->dwLastTick > __an_psInfo->dwDelayTime)
	{
		// ��������Ʈ ������ ����
		__an_psInfo = (SURFACEINFO*)__slGetNext();			
		pAi->dwLastTick = __an_dwThisTick;			
	}

	__slGetMember(&(pAi->slAnimation));	

	__gePutSprite(hdc, nX-__an_psInfo->nCentralX, nY-__an_psInfo->nCentralY, __an_psInfo, RGB(255, 255, 255));
}