#include "stdafx.h"

SURFACEINFO* __an_psInfo=0;	// 보존 대상 아님
DWORD __an_dwThisTick=0;	// 보존 대상 아님

void __anReset(SLMEMBER* pslmMember)
{	
	__slSetMember(pslmMember);
	__slSetHeadPosition();
	__slGetMember(pslmMember);
}

//// 현재 애니메이션 되고 있는 스프라이트의 사각영역 리턴
RECT __anGetCurSprRect(ANIINFO* pAi)
{
	RECT rcSpr =  {0,0,0,0};
	__slSetMember(&(pAi->slAnimation));
	__an_psInfo = (SURFACEINFO*)__slGetAt();
	// 노드가 초기화가 안되었거나 노드의 끝이면 리턴
	if (!__an_psInfo) return rcSpr;
	__slGetMember(&(pAi->slAnimation));	// 의미 없음
	SetRect(&rcSpr, 0, 0, __an_psInfo->nWidth, __an_psInfo->nHeight);
	OffsetRect(&rcSpr, -__an_psInfo->nCentralX, -__an_psInfo->nCentralY);
	return rcSpr;	
}

//// 한번만 반복
BOOL __anAnimateOnce(HDC hdc, int nX, int nY, ANIINFO* pAi)
{    
	__slSetMember(&(pAi->slAnimation));

	//// 현재 표면정보를 얻는다
	__an_psInfo = (SURFACEINFO*)__slGetAt();

	// 노드가 초기화가 안되었거나 노드의 끝이면 리턴
	if (!__an_psInfo) return FALSE;
	
	//// 스프라이트 프레임의 지연시간이 넘어갔는지?
	__an_dwThisTick = GetTickCount();	
	if (__an_dwThisTick - pAi->dwLastTick > __an_psInfo->dwDelayTime)
	{
		// 스프라이트 프레임 갱신
		__an_psInfo = (SURFACEINFO*)__slGetNext();			
		pAi->dwLastTick = __an_dwThisTick;			
	}

	__slGetMember(&(pAi->slAnimation));	

	__gePutSprite(hdc, nX-__an_psInfo->nCentralX, nY-__an_psInfo->nCentralY, __an_psInfo , RGB(255,255,255));

	return TRUE;
}

//// 무한 반복
void __anAnimate(HDC hdc, int nX, int nY, ANIINFO* pAi)
{    
	__slSetMember(&(pAi->slAnimation));

	//// 현재 표면정보를 얻는다
	__an_psInfo = (SURFACEINFO*)__slGetAt();

	// 노드가 초기화가 안되었거나 노드의 끝이면 리턴
	if (!__an_psInfo) 
	{				
		__slSetHeadPosition();
		__an_psInfo = (SURFACEINFO*)__slGetAt();
		if (!__an_psInfo) return;
	}
	
	//// 스프라이트 프레임의 지연시간이 넘어갔는지?
	__an_dwThisTick = GetTickCount();	
	if (__an_dwThisTick - pAi->dwLastTick > __an_psInfo->dwDelayTime)
	{
		// 스프라이트 프레임 갱신
		__an_psInfo = (SURFACEINFO*)__slGetNext();			
		pAi->dwLastTick = __an_dwThisTick;			
	}

	__slGetMember(&(pAi->slAnimation));	

	__gePutSprite(hdc, nX-__an_psInfo->nCentralX, nY-__an_psInfo->nCentralY, __an_psInfo, RGB(255, 255, 255));
}