#pragma once

#include "stdafx.h"



typedef struct DAMEMBERtag
{
	POINTXY*	pArray;		// 동적배열의 선두 주소
	int			nCount;		// 요소의 수
	int			nIndex;		// 인덱스
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

