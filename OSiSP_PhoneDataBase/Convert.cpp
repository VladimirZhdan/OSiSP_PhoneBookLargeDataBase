#include "stdafx.h"
#include "Convert.h"

void Convert::ConvertStringToLPTSTR(LPTSTR & desc, const string src)
{
	tstring tempSrc(src.begin(), src.end());
	desc = new TCHAR[src.size()];
	_tcscpy_s(desc, src.size(), tempSrc.c_str());		
	//desc[src.size()] = TEXT('\0');
}