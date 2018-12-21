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

//// Node�� �޸� ���� (pData�� pData���� �� �ٸ� �޸� �Ҵ��� �ִٸ� �̸� Get�Լ��� �����ؾ��Ѵ�)
void  __slRemoveHead();
void  __slRemoveTail();
void  __slRemoveAll();


