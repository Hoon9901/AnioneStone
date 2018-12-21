#include "stdafx.h"

NODE* __sl_pHead, *__sl_pTail, *__sl_pPosition;
int __sl_nCount;

//// 프로그램 실행시 최초에 한번만 실행한다
void __slInit()
{
	__sl_pHead = NULL;
	__sl_pTail = NULL;
	__sl_pPosition = __sl_pHead;
	
	__sl_nCount = 0;
}

//// 연결리스트 멤버 선언시 최초에 초기화

void __slInitMember(SLMEMBER* pslMember)
{
	pslMember->pHead = NULL;
	pslMember->pTail = NULL;
	pslMember->pPostion = pslMember->pHead;
	pslMember->nCount   = 0;
}

//// 다른 함수 호출전에 반드시 호출한다
void __slSetMember(SLMEMBER* pslMember)
{	
	__sl_pHead     = pslMember->pHead;
	__sl_pTail     = pslMember->pTail;
	__sl_pPosition = pslMember->pPostion;
	__sl_nCount    = pslMember->nCount;	
}

//// 다른 함수 호출후에 반드시 호출한다
//// 단, __slInitMember()를 호출하였으면 호출생략
void __slGetMember(SLMEMBER* pslMember)
{
	pslMember->pHead    = __sl_pHead;    
	pslMember->pTail    = __sl_pTail;   
	pslMember->pPostion = __sl_pPosition;
	pslMember->nCount   = __sl_nCount;
}

int __slGetCount()
{
	return __sl_nCount;
}

BOOL __slIsEmpty()
{
	if (__slGetCount())
		return TRUE;
	else
		return FALSE;
}

NODE* __slCreateNode(void* pData)
{
	NODE* pNode = (NODE*) malloc(sizeof(NODE));
	pNode->pData = pData;
	pNode->pNext = NULL;

	return pNode;
}

void __slSetHeadPosition()
{	
	__sl_pPosition = __sl_pHead;
}

void* __slGetAt()
{
	if (__sl_pPosition)
		return __sl_pPosition->pData;
	else
		return NULL;
}

//// 현재 Postion Node의 pData를 리턴하고 포지션을 증가
void* __slGetNext()
{
	if (__sl_pPosition)
	{
		NODE* pTemp = __sl_pPosition;
		__sl_pPosition = __sl_pPosition->pNext;
		return pTemp->pData;
	}
	else return NULL;
}

void* __slGetHead()
{
	if (__sl_pHead)
		return __sl_pHead->pData;
	else
		return NULL;
}

//// Tail Postion Node의 pData를 리턴
void* __slGetTail()
{
	if (__sl_pTail)
		return __sl_pTail->pData;
	else
		return NULL;
}

void __slAddTail(NODE* pNode)
{	
	NODE* pLast;

	if (__sl_pHead == NULL)		// Node가 없을때
	{
		__sl_pHead = pNode;
	}

	if (__sl_pTail)				// Node가 있을때
	{
		pLast = __sl_pTail;
		pLast->pNext = pNode;
		__sl_pTail = pNode;
	}
	else						// Node가 없을때
	{
		__sl_pTail = pNode;
	}

	__sl_nCount++;
}

void __slRemoveHead()
{
	//// Node가 하나일때
	if (__sl_pHead && __sl_pHead == __sl_pTail)
	{		
		free(__sl_pHead);
		__sl_pHead = __sl_pTail = NULL;
		__sl_nCount--;
	}
	//// Node가 두개 이상일때
	else if (__sl_pHead)
	{
		NODE* pSecond = __sl_pHead->pNext;
		free(__sl_pHead);
		__sl_pHead = pSecond;
		__sl_nCount--;
	}
}

void __slRemoveTail()
{
	//// Node가 하나일때
	if (__sl_pHead && __sl_pHead == __sl_pTail)
	{
		free(__sl_pHead);
		__sl_pHead = __sl_pTail = NULL;
		__sl_nCount--;
	}
	//// Node가 두개 이상일때
	else if (__sl_pHead)
	{
		int i;
		NODE* pNode = __sl_pHead;
		NODE* pNext;

		// 마지막에서 두번째 Node를 찾아낸다
		for (i=1; i < __sl_nCount-1; i++)
		{
			pNext = pNode->pNext;
			pNode = pNext;
		}

		pNode->pNext = NULL;
		free(__sl_pTail);
		__sl_pTail = pNode;
		__sl_nCount--;
	}
}

//// __slRemoveAll() 호출 후 __slInitMember()를 호출한다
void __slRemoveAll()
{
	NODE* pNext;
	NODE* pNode = __sl_pHead;

	while(pNode)
	{
		pNext = pNode->pNext;
		free(pNode);
		pNode = pNext;
	};
	__sl_nCount = 0;
}
