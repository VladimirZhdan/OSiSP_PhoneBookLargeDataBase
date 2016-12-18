#include "stdafx.h"
#include "PhoneDataBase.h"

tstring PhoneDataBase::libratyPath = _T("OSiSP_PhoneDataBase");

PhoneDataBase::PhoneDataBase(HWND hWnd)
{
	this->hWnd = hWnd;
	hLibrary = LoadLibrary(libratyPath.c_str());
	if (hLibrary)
	{
		Init();
	}
}


PhoneDataBase::~PhoneDataBase()
{
}

void PhoneDataBase::Init()
{
	pLoadPhoneBookList = (PLoadPhoneBookList)ImportFunction(_T("LoadPhoneBookList"));
}

FARPROC PhoneDataBase::ImportFunction(LPTSTR functionName)
{
	// Find analog GetProcAddress for LPWSTR
	FARPROC resultFunction = GetProcAddress(hLibrary, functionName);
	if (resultFunction == NULL)
	{
		MessageBox(hWnd, _T("Функция не найдена"),
			functionName, MB_OK | MB_ICONQUESTION);
		DestroyWindow(hWnd);
		return NULL;
	}	
	return resultFunction;
}

