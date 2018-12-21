#include "stdafx.h"

NODE* __sl_pHead, *__sl_pTail, *__sl_pPosition;
int __sl_nCount;

//// ���α׷� ����� ���ʿ� �ѹ��� �����Ѵ�
void __slInit()
{
	__sl_pHead = NULL;
	__sl_pTail = NULL;
	__sl_pPosition = __sl_pHead;
	
	__sl_nCount = 0;
}

//// ���Ḯ��Ʈ ��� ����� ���ʿ� �ʱ�ȭ

void __slInitMember(SLMEMBER* pslMember)
{
	pslMember->pHead = NULL;
	pslMember->pTail = NULL;
	pslMember->pPostion = pslMember->pHead;
	pslMember->nCount   = 0;
}

//// �ٸ� �Լ� ȣ������ �ݵ�� ȣ���Ѵ�
void __slSetMember(SLMEMBER* pslMember)
{	
	__sl_pHead     = pslMember->pHead;
	__sl_pTail     = pslMember->pTail;
	__sl_pPosition = pslMember->pPostion;
	__sl_nCount    = pslMember->nCount;	
}

//// �ٸ� �Լ� ȣ���Ŀ� �ݵ�� ȣ���Ѵ�
//// ��, __slInitMember()�� ȣ���Ͽ����� ȣ�����
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

//// ���� Postion Node�� pData�� �����ϰ� �������� ����
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

//// Tail Postion Node�� pData�� ����
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

	if (__sl_pHead == NULL)		// Node�� ������
	{
		__sl_pHead = pNode;
	}

	if (__sl_pTail)				// Node�� ������
	{
		pLast = __sl_pTail;
		pLast->pNext = pNode;
		__sl_pTail = pNode;
	}
	else						// Node�� ������
	{
		__sl_pTail = pNode;
	}

	__sl_nCount++;
}

void __slRemoveHead()
{
	//// Node�� �ϳ��϶�
	if (__sl_pHead && __sl_pHead == __sl_pTail)
	{		
		free(__sl_pHead);
		__sl_pHead = __sl_pTail = NULL;
		__sl_nCount--;
	}
	//// Node�� �ΰ� �̻��϶�
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
	//// Node�� �ϳ��϶�
	if (__sl_pHead && __sl_pHead == __sl_pTail)
	{
		free(__sl_pHead);
		__sl_pHead = __sl_pTail = NULL;
		__sl_nCount--;
	}
	//// Node�� �ΰ� �̻��϶�
	else if (__sl_pHead)
	{
		int i;
		NODE* pNode = __sl_pHead;
		NODE* pNext;

		// ���������� �ι�° Node�� ã�Ƴ���
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

//// __slRemoveAll() ȣ�� �� __slInitMember()�� ȣ���Ѵ�
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
