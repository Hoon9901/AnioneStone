#pragma once

#include "SLinkedList.h"

typedef struct ANIINFOTag
{
	SLMEMBER slAnimation;	// 애니메이션 연결리스트
	DWORD	 dwLastTick;	// 애니메이션에 사용	
} ANIINFO;

