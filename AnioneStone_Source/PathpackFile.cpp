#include "stdafx.h"

BOOL __ppSave(char* pstrFilename)
{
	FILE				*fp;
	PATHFILEHEADER		PathFileHeader;
		
	////
	PathFileHeader.nResolution = __daGetCount();
	if (PathFileHeader.nResolution)
	{
		memcpy(PathFileHeader.Symbol, PATHFILE_SYMBOL, sizeof(PathFileHeader.Symbol));
		////
		fp = fopen(pstrFilename, "wb");
		fwrite(&PathFileHeader, sizeof(PathFileHeader), 1, fp);
		fwrite(__daGetArray(), sizeof(POINTXY)*__daGetCount(), 1, fp);
		
		fclose(fp);

		return TRUE;
	}
	else return FALSE; 
}

BOOL __ppLoad(DAMEMBER* pdamPath, char* pstrFilename)
{
	FILE				*fp;
	PATHFILEHEADER		PathFileHeader;

	////
	fp = fopen(pstrFilename, "rb");
	fread(&PathFileHeader, sizeof(PathFileHeader), 1, fp);

	//// �н� �� �������� �˻��Ѵ�
	if (strcmp((char*)PathFileHeader.Symbol, PATHFILE_SYMBOL))
	{
		__daSetMember(pdamPath);
		__daInit(PathFileHeader.nResolution);
		fread(__daGetArray(), PathFileHeader.nResolution*sizeof(POINTXY), 1, fp);		
		__daGetMember(pdamPath);
		fclose(fp);
		return TRUE;
	}
	else
	{
		fclose(fp);
		return FALSE;
	}
}