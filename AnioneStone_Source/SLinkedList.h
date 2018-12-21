#pragma once

#include "stdafx.h"

typedef struct NODETag
{
	void*			pData;
	struct NODETag*	pNext;
} NODE;

typedef struct SLMEMBERtag
{
	NODE*	pHead;
	NODE*	pTail;
	NODE*	pPostion;
	int		nCount;
} SLMEMBER;

void  __slInit();
void  __slInitMember(SLMEMBER* pslMember);
void  __slSetMember(SLMEMBER* pslMember);
void  __slGetMember(SLMEMBER* pslMember);
int   __slGetCount();
BOOL  __slIsEmpty();
NODE* __slCreateNode(void* pData);
void  __slAddTail(NODE* pNode);

void  __slSetHeadPosition();
void* __slGetAt();
void* __slGetNext();
void* __slGetHead();
void* __slGetTail();

//// Node를 메모리 해제 (pData와 pData내에 또 다른 메모리 할당이 있다면 미리 Get함수로 제거해야한다)
void  __slRemoveHead();
void  __slRemoveTail();
void  __slRemoveAll();


