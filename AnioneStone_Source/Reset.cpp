#include "stdafx.h"

extern OBJCard * g_objCard;

void Reset()
{
	g_objCard->ObjCardSetnState(CARD_NORMAL);
	g_objCard->ObjCardSetnxny(125, 220);
}