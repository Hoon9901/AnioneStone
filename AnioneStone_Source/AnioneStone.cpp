#include "stdafx.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
void ___aMainLoop(HWND hWnd);
void ___aInit(HDC dcScreen);
void ___aDestroyAll();
void __bDisplayInfo();
int OnLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnLButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

HINSTANCE g_hInst;
HWND hWndMain;
LPSTR lpszClass="Anione Stone";

SURFACEINFO g_sfBack;			// �ĸ� ǥ��
// ���� ���� ����
OBJCard * g_objCard;
char * g_cScene; // ���� �� ��ġ
int CardState;
pos g_pos;
int RandCardNum[5]; // ī�� �ѹ� 
BOOL LbuttonDown;
bCardPackNum FaceCard;

 // Sound

FMOD_SYSTEM * g_System;
 FMOD_SOUND * g_Sound[MAX_SOUND];
 FMOD_SOUND * g_Effect[MAX_EFFECT];
 FMOD_CHANNEL * g_Channel[4];

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdParam,int nCmdShow)
{
  
	HWND hWnd;
	MSG msg;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(NULL_BRUSH);
	WndClass.hCursor=LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ANIONE));
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass, WS_SYSMENU | WS_CAPTION, //WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,HRES,VRES,
		NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);
	hWndMain=hWnd;

    while(1)
    {
    	if(PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ))
    	{
    	    if( !GetMessage( &msg, NULL, 0, 0 ) ) return (int) msg.wParam;
    	    TranslateMessage(&msg);
    	    DispatchMessage(&msg);
    	}
    	else ___aMainLoop(hWnd);
	}
	return (int)msg.wParam;
}

//// ���� �� �ʱ�ȭ
void ___aInit(HDC dcScreen)
{
	//// �ĸ�ǥ�� ����
	__geCreateBackBuffer(dcScreen, HRES, VRES, 32, &g_sfBack);
	g_cScene = "����";
	//// ��� �ʱ�ȭ
	__slInit();						// SLinked List
	__syInit(dcScreen, VRES);		// Scenery
	//// ������Ʈ �ʱ�ȭ
	g_objCard = new OBJCard(dcScreen);
	////	Sound
	FMOD_System_Create(&g_System);
	FMOD_System_Init(g_System, MAX_CHANNELS, FMOD_INIT_NORMAL, NULL);
	// �������
	FMOD_System_CreateStream(g_System, ".\\Sound\\MainTitle.mp3", FMOD_LOOP_NORMAL, 0, &g_Sound[0]);
	FMOD_System_CreateStream(g_System, ".\\Sound\\ī����.mp3", FMOD_LOOP_NORMAL, 0, &g_Sound[1]);
	// ȿ����
	FMOD_System_CreateSound(g_System, ".\\Sound\\Ŭ��.mp3", FMOD_DEFAULT, 0, &g_Effect[0]);
	FMOD_System_CreateSound(g_System, ".\\Sound\\����.mp3", FMOD_DEFAULT, 0, &g_Effect[1]);
	FMOD_System_CreateSound(g_System, ".\\Sound\\ī�弱��.mp3", FMOD_DEFAULT, 0, &g_Effect[2]);
	FMOD_System_CreateSound(g_System, ".\\Sound\\����.mp3", FMOD_DEFAULT, 0, &g_Effect[3]);
	FMOD_System_CreateSound(g_System, ".\\Sound\\AdventurePanel_up.mp3", FMOD_DEFAULT, 0, &g_Effect[4]);
	FMOD_System_CreateSound(g_System, ".\\Sound\\AdventurePanel_down.mp3", FMOD_DEFAULT, 0, &g_Effect[5]);

	FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[0], 0, &g_Channel[0]); // ���
	FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Effect[3], 0, &g_Channel[3]); // ���

	CardSoundInit();
}

//// �ϰ� �ı�
void ___aDestroyAll()
{
	CardSoundRelease();
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		FMOD_Sound_Release(g_Effect[i]);
	}

	for (int i = 0; i < MAX_SOUND; i++)
	{
		FMOD_Sound_Release(g_Sound[i]);
	}
	FMOD_System_Close(g_System);
	FMOD_System_Release(g_System);
	__syRelease();
	__geReleaseSurface(&g_sfBack);	
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC dcScreen;
	
	switch(iMessage)
	{
	case WM_TIMER:
		break;
	case WM_CREATE:
		//// �ʱ�ȭ
		dcScreen = GetDC(hWnd);	
		___aInit(dcScreen);
		ReleaseDC(hWnd, dcScreen);
		return 0;
	case WM_KEYDOWN:
		{
			//__goRelease();		
		}
		return 0;
	case WM_MOUSEMOVE:
	{
						 g_pos.posX = LOWORD(lParam);
						 g_pos.posY = HIWORD(lParam);
	}
		break;
	case WM_LBUTTONDOWN:
		return OnLButtonDown(hWnd, wParam, lParam);
	case WM_LBUTTONUP:
		return OnLButtonUp(hWnd, wParam, lParam);
	case WM_DESTROY:
		___aDestroyAll();
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

int OnLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (!strcmp(g_cScene, "����"))
	{	
		if ((g_pos.posX >= 400 && g_pos.posX <= 542) && (g_pos.posY >= 554 && g_pos.posY <= 642)) // ���� -> �Ѱ���
	{

		g_cScene = "�Ѱ���";
		__syInit(g_sfBack.dcSurface, VRES);
		FMOD_Channel_Stop(g_Channel[0]);
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Effect[0], 0, &g_Channel[3]); // ���
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1]); // ���
		srand((unsigned)time(NULL));
		int i; int j; int k;
		for (i = 0; i < 5; i++) // �ߺ� ����
		{
			RandCardNum[i] = rand() % 20;
		}
	}
	}
	else if (!strcmp(g_cScene, "�Ѱ���"))
	{
		
		if (CardState == CARD_NORMAL) // ī�� ���°� �븻�̰� ���콺����Ŭ�� �ߵ� ��ǥ�� �浹üũ�� �ߵ�������
		{
			if ((g_pos.posX >= 125 && g_pos.posX <= 295) && (g_pos.posY >= 220 && g_pos.posY <= 460))
			{
				CardState = CARD_CLICK;
				LbuttonDown =  TRUE;
			}
		}
		if (CardState == CARD_ACTION)
		{
			if (FaceCard.card[0] == FALSE)
			{
				if ((g_pos.posX >= 500 && g_pos.posX <= 500 + CARD_WIDTH) &&
					(g_pos.posY >= 150 && g_pos.posY <= 150 + CARD_HEIGHT))
				{
					FaceCard.card[0] = TRUE;
					CardOfRating(RandCardNum[0]);
					FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Effect[2], 0, &g_Channel[3]); // ���
				}
			}
			if (FaceCard.card[1] == FALSE)
			{
				if ((g_pos.posX >= 750 && g_pos.posX <= 750 + CARD_WIDTH) &&
					(g_pos.posY >= 75 && g_pos.posY <= 75 + CARD_HEIGHT))
				{
					FaceCard.card[1] = TRUE;
					CardOfRating(RandCardNum[1]);
					FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Effect[2], 0, &g_Channel[3]); // ���
				}
			}
			if (FaceCard.card[2] == FALSE){
				if ((g_pos.posX >= 1000 && g_pos.posX <= 1000 + CARD_WIDTH) &&
					(g_pos.posY >= 150 && g_pos.posY <= 150 + CARD_HEIGHT))
				{
					FaceCard.card[2] = TRUE;
					CardOfRating(RandCardNum[2]);
					FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Effect[2], 0, &g_Channel[3]); // ���
				}

			}
			if (FaceCard.card[3] == FALSE){
				if ((g_pos.posX >= 630 && g_pos.posX <= 630 + CARD_WIDTH) &&
					(g_pos.posY >= 420 && g_pos.posY <= 420 + CARD_HEIGHT))
				{
					FaceCard.card[3] = TRUE;
					CardOfRating(RandCardNum[3]);
					FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Effect[2], 0, &g_Channel[3]); // ���
				}

			}
			if (FaceCard.card[4] == FALSE){
				if ((g_pos.posX >= 870 && g_pos.posX <= 870 + CARD_WIDTH) &&
					(g_pos.posY >= 420 && g_pos.posY <= 420 + CARD_HEIGHT))
				{
					FaceCard.card[4] = TRUE;
					CardOfRating(RandCardNum[4]);
					FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Effect[2], 0, &g_Channel[3]); // ���
				}

			}
		}
		if ((g_pos.posX >= 132 && g_pos.posX <= 266)&& (g_pos.posY >= 633 && g_pos.posY <= 683)) // ���� -> �Ѱ���
		{ 
			

			g_cScene = "����";
			__syInit(g_sfBack.dcSurface, VRES);
			
			// -- �ʱ�ȭ
			if (g_objCard->ObjCardGetnState() == CARD_ACTION)
			{
				CardState = CARD_NORMAL;
				LbuttonDown = FALSE;
				Reset();
				for (int i = 0; i < 5; i++)
				{
					FaceCard.card[i] = FALSE;
					RandCardNum[i] = NULL;
				}
			}
			FMOD_Channel_Stop(g_Channel[1]);
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Effect[1], 0, &g_Channel[3]); // ���
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[0], 0, &g_Channel[0]); // ���
		}
	}
	return 1;
}

int OnLButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (CardState == CARD_CLICK)
	{
		CardState = CARD_NORMAL;
		LbuttonDown = FALSE;
	}
	return 1;
}

void ___aMainLoop(HWND hWnd)
{
	HDC   dcScreen;
	
	// ��� ������Ʈ
	g_objCard->ObjCardAction();
	
	//// ���	
	// ���
	__syPutScenery(g_sfBack.dcSurface);

	// ������Ʈ
	g_objCard->ObjCardRender(g_sfBack.dcSurface);
	
	//// ���� ���� ���
#ifdef _DEBUG
	__bDisplayInfo();
#endif // !_DEBUG

	
	// ���� ����
	FMOD_System_Update(g_System);

	dcScreen = GetDC(hWnd);
	//// ��� �Ϸ� (�ĸ�ǥ��DC --����--> ȭ��DC)
	__geCompleteBlt(dcScreen, &g_sfBack);
	ReleaseDC(hWnd, dcScreen);

	//// FPS ����
	Sleep(1000/60);
}

void __bDisplayInfo()
{
	
	////				
	char  strBuff[255];

	//// ��Ʈ�� ������ �������� ����Ѵ�
	SetBkMode(g_sfBack.dcSurface, TRANSPARENT);

	//// ��Ʈ������ ����
	SetTextColor(g_sfBack.dcSurface, RGB(1, 255, 255));

	wsprintf(strBuff, "Mouse X = %d Mouse Y = %d", g_pos.posX, g_pos.posY);
	TextOut(g_sfBack.dcSurface, 5, 5, strBuff, (int)strlen(strBuff));
}
