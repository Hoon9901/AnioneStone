#pragma once

#include "stdafx.h"



typedef struct DAMEMBERtag
{
	POINTXY*	pArray;		// �����迭�� ���� �ּ�
	int			nCount;		// ����� ��
	int			nIndex;		// �ε���
} DAMEMBER;

void __daInit(int nCount);
void __daSetMember(DAMEMBER* pdaMember);
void __daGetMember(DAMEMBER* pdaMember);
void __daRemoveAll();
int  __daGetCount();

void	 __daCopyArray(POINTXY* pArray, int nSize);
void     __daSetElement(int nIndex, POINTXY xyValue);
POINTXY  __daGetElement(int nIndex);
POINTXY  __daGetNext();
POINTXY* __daGetArray();

