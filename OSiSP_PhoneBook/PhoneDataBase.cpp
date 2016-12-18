#include "stdafx.h"
#include "PhoneDataBase.h"

const tstring PhoneDataBase::libratyPath(_T("OSiSP_PhoneDataBase"));

PhoneDataBase::PhoneDataBase(HWND hWnd)
{
	this->hWnd = hWnd;
	//hLibrary = LoadLibrary(libratyPath.c_str());
	hLibrary = LoadLibrary(_T("OSiSP_PhoneDataBase"));
	if (hLibrary)
	{
		isReadyToWork = true;
		Init();
	}
	else
	{
		isReadyToWork = false;
		MessageBox(hWnd, _T("Библиотека не найдена"), _T("LoadLibrary"), MB_OK | MB_ICONQUESTION);		
	}
}

bool PhoneDataBase::IsReadyToWork()
{
	return isReadyToWork;
}

std::vector<PhoneBookNode*>* PhoneDataBase::LoadPhoneBookList(LPTSTR fileName)
{
	if (pLoadPhoneBookList != NULL)
	{
		return pLoadPhoneBookList(fileName);
	}
	else
	{
		return nullptr;
	}
}


PhoneDataBase::~PhoneDataBase()
{
	FreeLibrary(hLibrary);
}

void PhoneDataBase::Init()
{
	pLoadPhoneBookList = (PLoadPhoneBookList)ImportFunction(_T("LoadPhoneBookList"));
}

FARPROC PhoneDataBase::ImportFunction(tstring functionName)
{
	std::string tempFunctionName(functionName.begin(), functionName.end());	
	FARPROC resultFunction = GetProcAddress(hLibrary, tempFunctionName.c_str());
	if (resultFunction == NULL)
	{
		MessageBox(hWnd, _T("Функция не найдена"), functionName.c_str(), MB_OK | MB_ICONQUESTION);		
		return nullptr;
	}	
	return resultFunction;
}

