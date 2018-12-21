#include "stdafx.h"

FMOD_SOUND * cardturnoverEffect[4];
FMOD_SOUND * cardOpenVoice[4];
extern  FMOD_SYSTEM * g_System;
extern FMOD_CHANNEL * g_Channel[4];

int ThisCardRating;

void CardSoundInit()
{
	// 카드 오픈시 나는 효과음
	FMOD_System_CreateSound(g_System, ".\\Sound\\card_turn_over_normal.mp3", FMOD_DEFAULT, 0, &cardturnoverEffect[0]);
	FMOD_System_CreateSound(g_System, ".\\Sound\\card_turn_over_rare.mp3", FMOD_DEFAULT, 0, &cardturnoverEffect[1]);
	FMOD_System_CreateSound(g_System, ".\\Sound\\card_turn_over_epic.mp3", FMOD_DEFAULT, 0, &cardturnoverEffect[2]);
	FMOD_System_CreateSound(g_System, ".\\Sound\\card_turn_over_legendary.mp3", FMOD_DEFAULT, 0, &cardturnoverEffect[3]);
	// 여관 주인 음성
	FMOD_System_CreateSound(g_System, ".\\Sound\\희귀카드.mp3", FMOD_DEFAULT, 0, &cardOpenVoice[0]);
	FMOD_System_CreateSound(g_System, ".\\Sound\\영웅카드.mp3", FMOD_DEFAULT, 0, &cardOpenVoice[1]);
	FMOD_System_CreateSound(g_System, ".\\Sound\\전설카드.mp3", FMOD_DEFAULT, 0, &cardOpenVoice[2]);
	FMOD_System_CreateSound(g_System, ".\\Sound\\황금전설카드.mp3", FMOD_DEFAULT, 0, &cardOpenVoice[3]);

}


void CardSoundRelease()
{
	for (int i = 0; i < 4; i++)
	{
		FMOD_Sound_Release(cardOpenVoice[i]);
		FMOD_Sound_Release(cardturnoverEffect[i]);
	}
}

void CardOfRating(int RandCardNum)
{
	switch (RandCardNum)
	{
	case 9: // Normal
		ThisCardRating = 0;
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, cardturnoverEffect[0], 0, &g_Channel[3]); // 재생
		break;
	case 1: // Rare
	case 11:
	case 16:
	case 19:
		ThisCardRating = rare;
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, cardturnoverEffect[1], 0, &g_Channel[3]); // 재생
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, cardOpenVoice[0], 0, &g_Channel[4]); // 재생
		break;
	case 0: //Epic
	case 3:
	case 6:
	case 10:
	case 12:
	case 17:
	case 18:
		ThisCardRating = epic;
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, cardturnoverEffect[2], 0, &g_Channel[3]); // 재생
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, cardOpenVoice[1], 0, &g_Channel[4]); // 재생
		break;
	case 2: // Legendary
	case 5:
	case 4:
	case 14:
		ThisCardRating = legendary;
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, cardturnoverEffect[3], 0, &g_Channel[3]); // 재생
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, cardOpenVoice[2], 0, &g_Channel[4]); // 재생
		break;
	case 7:
	case 13:
	case 8: // Gold Legendary
	case 15:
		ThisCardRating = legendary;
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, cardturnoverEffect[3], 0, &g_Channel[3]); // 재생
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, cardOpenVoice[3], 0, &g_Channel[4]); // 재생
		break;
	}
	FMOD_Channel_SetVolume(g_Channel[4], 0.8f); // 보이스
	FMOD_Channel_SetVolume(g_Channel[3], 0.4f); // 카드 여는 소리

}