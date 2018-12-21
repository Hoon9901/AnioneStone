#include "stdafx.h"

POINTXY __pixyPath;

POINTXY __piGetNextPathPoint(DAMEMBER* pDamPath)
{	
	__daSetMember(pDamPath);
	__pixyPath = __daGetNext();
	__daGetMember(pDamPath);

	return __pixyPath;
}

void __piRelease(DAMEMBER* pDamPath)
{
	__daSetMember(pDamPath);
	__daRemoveAll();
}