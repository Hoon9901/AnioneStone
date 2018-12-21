#include "stdafx.h"

BOOL __afSave(SLMEMBER* pslm, char* pstrFilename)
{
	FILE				*fp;
	ANIFILEHEADER		AniFileHeader;
	BIN_SURFACEINFO*	pbsInfo;
	DWORD dwSizeSurface=0;
		
	////
	__slSetMember(pslm);
	AniFileHeader.nFrameCount = __slGetCount();	
	if (AniFileHeader.nFrameCount)
	{
		memcpy(AniFileHeader.Symbol, ANIM_FILE_SYMBOL, sizeof(AniFileHeader.Symbol));
		////
		fp = fopen(pstrFilename, "wb");
		fwrite(&AniFileHeader, sizeof(AniFileHeader), 1, fp);

		////
		__slSetHeadPosition();
		while(pbsInfo = (BIN_SURFACEINFO*)__slGetNext())
		{
			dwSizeSurface = pbsInfo->nWidth * pbsInfo->nHeight * 3;
			fwrite(&pbsInfo->nWidth, sizeof(pbsInfo->nWidth), 1, fp);
			fwrite(&pbsInfo->nHeight, sizeof(pbsInfo->nHeight), 1, fp);
			fwrite(&pbsInfo->nCentralX, sizeof(pbsInfo->nCentralX), 1, fp);
			fwrite(&pbsInfo->nCentralY, sizeof(pbsInfo->nCentralY), 1, fp);
			fwrite(&pbsInfo->crColorKey, sizeof(pbsInfo->crColorKey), 1, fp);
			fwrite(&pbsInfo->dwDelayTime, sizeof(pbsInfo->dwDelayTime), 1, fp);
			fwrite(pbsInfo->pSurface, dwSizeSurface, 1, fp);
		}
		__slGetMember(pslm);

		fclose(fp);

		return TRUE;
	}
	else return FALSE; // 변동 사항이 없으므로 __slGetMember() 호출 생략
}

BOOL __afLoad(SLMEMBER* pslm, char* pstrFilename)
{
	FILE				*fp;
	ANIFILEHEADER		AniFileHeader;	
	BIN_SURFACEINFO*	pbsInfo;
	DWORD dwSizeSurface=0;
		
	////
	fp = fopen(pstrFilename, "rb");
	fread(&AniFileHeader, sizeof(AniFileHeader), 1, fp);

	//// 애니메이션파일인지 검사한다
	if (strcmp((char*)AniFileHeader.Symbol, ANIM_FILE_SYMBOL))
	{
		__slSetMember(pslm);
		__slSetHeadPosition();
		for (int i=0; i < AniFileHeader.nFrameCount; i++)
		{
			pbsInfo = __geCreateSprBinSurface();
			
			fread(&pbsInfo->nWidth, sizeof(pbsInfo->nWidth), 1, fp);
			fread(&pbsInfo->nHeight, sizeof(pbsInfo->nHeight), 1, fp);
			fread(&pbsInfo->nCentralX, sizeof(pbsInfo->nCentralX), 1, fp);
			fread(&pbsInfo->nCentralY, sizeof(pbsInfo->nCentralY), 1, fp);
			fread(&pbsInfo->crColorKey, sizeof(pbsInfo->crColorKey), 1, fp);
			fread(&pbsInfo->dwDelayTime, sizeof(pbsInfo->dwDelayTime), 1, fp);

			dwSizeSurface = pbsInfo->nWidth * pbsInfo->nHeight * 3;
			pbsInfo->pSurface = (BYTE*) malloc(dwSizeSurface);
			fread(pbsInfo->pSurface, dwSizeSurface, 1, fp);		

			__slAddTail(__slCreateNode(pbsInfo));
		}
		__slGetMember(pslm);

		fclose(fp);
		return TRUE;
	}
	else
	{
		fclose(fp);

		HWND hWnd = FindWindow("스프라이트 툴", "스프라이트 툴");
		MessageBox (hWnd, "애니메이션 파일이 아닙니다",
			     	"파일열기", MB_ICONEXCLAMATION | MB_OK) ;
		return FALSE;
	}
}

BOOL __afLoad2MemDc(SLMEMBER* pslm, char* pstrFilename, HDC hdc)
{
	FILE				*fp;
	ANIFILEHEADER		AniFileHeader;	
	SURFACEINFO*		psInfo;
	BYTE*				pSurface;
	DWORD				dwSizeSurface=0;
		
	////
	fp = fopen(pstrFilename, "rb");
	fread(&AniFileHeader, sizeof(AniFileHeader), 1, fp);

	//// 애니메이션파일인지 검사한다
	if (strcmp((char*)AniFileHeader.Symbol, ANIM_FILE_SYMBOL))
	{
		__slSetMember(pslm);
		__slSetHeadPosition();
		for (int i=0; i < AniFileHeader.nFrameCount; i++)
		{
			psInfo = __geCreateSprSurface();
			
			fread(&psInfo->nWidth, sizeof(psInfo->nWidth), 1, fp);
			fread(&psInfo->nHeight, sizeof(psInfo->nHeight), 1, fp);
			fread(&psInfo->nCentralX, sizeof(psInfo->nCentralX), 1, fp);
			fread(&psInfo->nCentralY, sizeof(psInfo->nCentralY), 1, fp);
			fread(&psInfo->crColorKey, sizeof(psInfo->crColorKey), 1, fp);
			fread(&psInfo->dwDelayTime, sizeof(psInfo->dwDelayTime), 1, fp);
			dwSizeSurface = psInfo->nWidth * psInfo->nHeight * 3;
			pSurface = (BYTE*) malloc(dwSizeSurface);			
			fread(pSurface, dwSizeSurface, 1, fp);						// 이진 데이터를 읽는다

			psInfo->hBmp= __geSurface2BmpHandle(psInfo, pSurface);		// 비트맵 핸들로 변환
			__geLoadSurface(hdc, psInfo);								// 적재
			free(pSurface);

			__slAddTail(__slCreateNode(psInfo));
		}
		__slGetMember(pslm);

		fclose(fp);
		return TRUE;
	}
	else
	{
		fclose(fp);
		return FALSE;
	}
}