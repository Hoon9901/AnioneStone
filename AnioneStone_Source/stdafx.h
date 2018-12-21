#pragma once


//Define 
#define ANIM_FILE_SYMBOL "ANIM"
#define CARD_NORMAL 0 
#define CARD_CLICK	1
#define CARD_ACTION  2
#define PATHFILE_SYMBOL "PATH"
#define Card_Width 200
#define Card_Height 270
#define MAX_CHANNELS 10
#define MAX_SOUND 2
#define MAX_EFFECT 6
#define HRES		1280
#define VRES		720
#define MAX_OBJECT	500
#define CARD_WIDTH 180
#define CARD_HEIGHT 250
#define CARD_MAX 20
#define IDI_ANIONE   5
#define DA_END -999

// 기본
#include "targetver.h"

// Windows 헤더 파일:
#include <windows.h>
#include <mmsystem.h>

// C의 런타임 헤더 파일입니다.
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <fmod.h>

//#define TRACEON
//#include <ErrTrace.h>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.


#include "AnimationInfo.h"
#include "TypeDef.h"
#include "GraphicEngine.h"
#include "Animation.h"
#include "SLinkedList.h"
#include "AnimationFile.h"
#include "AnioneStone.h"
#include "CardRating.h"
#include "DynamicArray.h"
#include "ObjCard.h"
#include "PathpackFile.h"
#include "PathInfo.h"
#include "ReleaseSurfaceAll.h"
#include "resource3.h"
#include "Scenery.h"

#include "Reset.h"

enum{
	rare = 1, epic , legendary
};

