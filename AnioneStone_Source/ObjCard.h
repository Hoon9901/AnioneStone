#pragma once

#include "stdafx.h"

class OBJCard
{
private:
	int			nX;
	int			nY;
	int			nState;			// ���� ����	
	SURFACEINFO sfCard;
	ANIINFO aiRare;
	ANIINFO aiEpic;
	ANIINFO ailegen;
public:
	OBJCard(HDC hdc);
	~OBJCard();
	void ObjCardAction();
	void ObjCardRender(HDC hdc);
	void CheckThisRating(int num, int x, int y, HDC hdc);
	int ObjCardGetnState();

	void* ObjCardCreate(int nSize);
	void* ObjCardGetInfo();
	void  ObjCardSetMember(void* pObjInfo);
	void  ObjCardGetMember(void* pObjInfo);
	void  ObjCardSetnState(int n);
	void  ObjCardSetnxny(int x, int y);
};

