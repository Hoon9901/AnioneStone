#include "stdafx.h"

extern char * g_cScene; // 캐릭터
extern int CardState;
extern pos g_pos;
extern BOOL LbuttonDown;
extern bCardPackNum FaceCard;
SURFACEINFO sfCardOpen[5];
SURFACEINFO sfCardPack[CARD_MAX];
extern int RandCardNum[5];

OBJCard::OBJCard( HDC hdc)
{
	this->nX = 125;
	this->nY = 220;
	this->nState = CARD_NORMAL;

	__geSetSprSurface(&this->sfCard, RGB(255, 255, 255));
	this->sfCard.hBmp = __geBmpFile2BmpHandle(".\\Data\\DOS\\카드.bmp");
	__geLoadSurface(hdc, &this->sfCard);

	for (int i = 0; i < 5; i++)
	{
		__geSetSprSurface(&sfCardOpen[i], RGB(255, 255, 255));
		sfCardOpen[i].hBmp = __geBmpFile2BmpHandle(".\\Data\\DOS\\카드뒷면.bmp");
		__geLoadSurface(hdc, &sfCardOpen[i]);
	}

	char str[128];
	for (int i = 0; i < CARD_MAX; i++)
	{   // 카드 이미지 로드
		wsprintf(str, ".\\Data\\CardPack\\%d.bmp", i);
		__geSetSprSurface(&sfCardPack[i], RGB(0, 0, 0));
		sfCardPack[i].hBmp = __geBmpFile2BmpHandle(str);
		__geLoadSurface(hdc, &sfCardPack[i]);

	}
	__slInitMember(&aiRare.slAnimation);
	__afLoad2MemDc(&aiRare.slAnimation, ".\\Data\\Ani\\희귀카드.ani", hdc);

	__slInitMember(&aiEpic.slAnimation);
	__afLoad2MemDc(&aiEpic.slAnimation, ".\\Data\\Ani\\전설카드.ani", hdc);

	__slInitMember(&ailegen.slAnimation);
	__afLoad2MemDc(&ailegen.slAnimation, ".\\Data\\Ani\\황금카드.ani", hdc);

}

OBJCard::~OBJCard()
{
	__ReleaseSurfaceAll(&ailegen.slAnimation);
	__ReleaseSurfaceAll(&aiEpic.slAnimation);
	__ReleaseSurfaceAll(&aiRare.slAnimation);
}

void OBJCard::ObjCardAction()
{
	if (g_cScene == "팩개봉")
	{
		switch (this->nState)
		{
		case CARD_NORMAL:
		{
							if (CardState == CARD_CLICK)
							{
								this->nState = CARD_CLICK;
							}
							break;
		}
		case CARD_CLICK:
		{
						   if (LbuttonDown == TRUE)
						   {
							   this->nX = g_pos.posX - (184 / 2);
							   this->nY = g_pos.posY - (249 / 2);
						   }
						   else
						   {
							   if (g_pos.posX >= 458)
							   {
								   this->nX = 731;
								   this->nY = 255;
								   this->nState = CARD_ACTION;
								   CardState = this->nState;
							   }
							   else
							   {
								   LbuttonDown = FALSE;
								   this->nState = CARD_NORMAL;
								   this->nX = 125;
								   this->nY = 220;
							   }
						   }
						   break;
		}
		case CARD_ACTION:
			break;
		}
	}
}

void OBJCard::ObjCardRender(HDC hdc)
{
	if (g_cScene == "팩개봉")
	{
		switch (this->nState)
		{
		case CARD_NORMAL:
			__gePutSprite(hdc, this->nX, this->nY, &this->sfCard);
			break;
		case CARD_CLICK:
			__gePutSprite(hdc, this->nX, this->nY, &this->sfCard);
			break;
		case CARD_ACTION: 
			if (FaceCard.card[0])
			{
				CheckThisRating(RandCardNum[0], 500, 150, hdc);
				__gePutSprite(hdc, 500, 150, &sfCardPack[RandCardNum[0]]);
			}
			else
			{
				__gePutSprite(hdc, 500, 150, &sfCardOpen[0]);
			}
			if (FaceCard.card[1])
			{
				CheckThisRating(RandCardNum[1], 750, 75, hdc);
				__gePutSprite(hdc, 750, 75, &sfCardPack[RandCardNum[1]]);
			}
			else
			{
				__gePutSprite(hdc, 750, 75, &sfCardOpen[1]);
			}
			if (FaceCard.card[2])
			{
				CheckThisRating(RandCardNum[2], 1000, 150, hdc);
				__gePutSprite(hdc, 1000, 150, &sfCardPack[RandCardNum[2]]);
			}
			else
			{
				__gePutSprite(hdc, 1000, 150, &sfCardOpen[2]);
			}
			if (FaceCard.card[3])
			{
				CheckThisRating(RandCardNum[3], 630, 420, hdc);
				__gePutSprite(hdc, 630, 420, &sfCardPack[RandCardNum[3]]);
			}
			else
			{
				__gePutSprite(hdc, 630, 420, &sfCardOpen[3]);
			}
			if (FaceCard.card[4])
			{
				CheckThisRating(RandCardNum[4], 870, 420, hdc);
				__gePutSprite(hdc, 870, 420, &sfCardPack[RandCardNum[4]]);
			}
			else
			{
				__gePutSprite(hdc, 870, 420, &sfCardOpen[4]);
			}
			break;
		}
	}
}

int OBJCard::ObjCardGetnState()
{
	return nState;
}

void OBJCard::CheckThisRating(int num, int x, int y, HDC hdc)
{
	switch (num)
	{
	case 9: // Normal
		break;
	case 1: // Rare
	case 11:
	case 16:
	case 19:
		__anAnimate(hdc, x + (Card_Width / 2), y + (Card_Height / 2), &aiRare);
		break;
	case 0: //Epic
	case 3:
	case 6:
	case 10:
	case 12:
	case 17:
	case 18:
		__anAnimate(hdc, x + (Card_Width / 2), y + (Card_Height / 2), &aiEpic);
		break;
	case 2: // Legendary
	case 5:
	case 4:
	case 14:
		__anAnimate(hdc, x + (Card_Width / 2), y + (Card_Height / 2), &ailegen);
		break;
	case 7:// Gold Legendary
	case 13:
	case 8: 
	case 15:
		__anAnimate(hdc, x + (Card_Width / 2), y + (Card_Height / 2), &ailegen);
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////

void* OBJCard::ObjCardCreate(int nSize)
{
	return malloc(nSize);
}

void* OBJCard::ObjCardGetInfo()
{
	return this;
}

//// 최초에 한번 호출됨
void  OBJCard::ObjCardSetMember(void* pObjInfo)
{
	//this = (OBJCARD*)pObjInfo;
}

//// GObject에서 일괄호출시 호출되나 의미 없음 (유일객체임으로)
void  OBJCard::ObjCardGetMember(void* pObjInfo)
{
	pObjInfo = (void*)this;
}


void OBJCard::ObjCardSetnState(int n)
{
	this->nState = n;
}

void OBJCard::ObjCardSetnxny(int x, int y)
{
	this->nX = x;
	this->nY = y;
}