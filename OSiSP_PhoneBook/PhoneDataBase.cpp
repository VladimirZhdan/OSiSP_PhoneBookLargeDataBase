#include "stdafx.h"
#include "PhoneDataBase.h"

PhoneDataBase::PhoneDataBase(HWND hWnd, LPTSTR libraryFilePath)
{
	this->hWnd = hWnd;
	this->libraryFilePath = libraryFilePath;	
	hLibrary = LoadLibrary(_T("OSiSP_PhoneDataBaseLarge"));
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

unsigned long PhoneDataBase::LoadCountOfPhoneBookNode()
{
	if (pLoadCountOfPhoneBookNode != NULL)
	{
		return pLoadCountOfPhoneBookNode(libraryFilePath);
	}
	else
	{
		return 0;
	}
}

PhoneBookNode * PhoneDataBase::LoadPhoneBookNode(unsigned long index)
{
	if (pLoadPhoneBookNode != NULL)
	{
		return pLoadPhoneBookNode(index);
	}
	else
	{
		return nullptr;
	}
}

std::vector<PhoneBookNode*>* PhoneDataBase::LoadSearchPhoneBookList(PhoneBookNode * searchedPhoneBookNode)
{
	if (pLoadSearchPhoneBookList != NULL)
	{
		return pLoadSearchPhoneBookList(searchedPhoneBookNode);
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
	pLoadCountOfPhoneBookNode = (PLoadCountOfPhoneBookNode)ImportFunction(_T("LoadCountOfPhoneBookNode"));
	pLoadPhoneBookNode = (PLoadPhoneBookNode)ImportFunction(_T("LoadPhoneBookNode"));
	pLoadSearchPhoneBookList = (PLoadSearchPhoneBookList)ImportFunction(_T("LoadSearchPhoneBookList"));
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

