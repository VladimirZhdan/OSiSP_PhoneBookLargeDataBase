#include "stdafx.h"
#include "Convert.h"

void Convert::ConvertStringToLPTSTR(LPTSTR & desc, const string src)
{
	tstring tempSrc(src.begin(), src.end());
	int descSize = (src.size() + 1);
	desc = new TCHAR[descSize];
	_tcscpy_s(desc, descSize, tempSrc.c_str());			
}