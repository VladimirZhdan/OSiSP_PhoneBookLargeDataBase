#include "stdafx.h"
#include "PhoneDataBase.h"

PhoneDataBase::PhoneDataBase(HWND hWnd, LPTSTR libraryFilePath)
{
	this->hWnd = hWnd;
	this->libraryFilePath = libraryFilePath;	
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

std::vector<PhoneBookNode*>* PhoneDataBase::LoadPhoneBookList()
{
	if (pLoadPhoneBookList != NULL)
	{
		return pLoadPhoneBookList(libraryFilePath);
	}
	else
	{
		return nullptr;
	}
}

std::vector<PhoneBookNode*>* PhoneDataBase::LoadSearchPhoneBookListUsingSurname(LPTSTR searchSurname)
{
	if (pLoadSearchPhoneBookListUsingSurname != NULL)
	{
		return pLoadSearchPhoneBookListUsingSurname(searchSurname, libraryFilePath);
	}
	else
	{
		return nullptr;
	}
}

std::vector<PhoneBookNode*>* PhoneDataBase::LoadSearchPhoneBookListUsingTelephone(LPTSTR searchTelephone)
{
	if (pLoadSearchPhoneBookListUsingTelephone != NULL)
	{
		return pLoadSearchPhoneBookListUsingTelephone(searchTelephone, libraryFilePath);
	}
	else
	{
		return nullptr;
	}
}

std::vector<PhoneBookNode*>* PhoneDataBase::LoadSearchPhoneBookListUsingStreet(LPTSTR searchStreet)
{
	if (pLoadSearchPhoneBookListUsingStreet != NULL)
	{
		return pLoadSearchPhoneBookListUsingStreet(searchStreet, libraryFilePath);
	}
	else
	{
		return nullptr;
	}
}

void PhoneDataBase::EditPhoneBookNode(PhoneBookNode * phoneBookNode)
{
	if (pEditPhoneBookNode != NULL)
	{
		pEditPhoneBookNode(phoneBookNode, libraryFilePath);
	}	
}


PhoneDataBase::~PhoneDataBase()
{
	FreeLibrary(hLibrary);
}

void PhoneDataBase::Init()
{
	pLoadPhoneBookList = (PLoadPhoneBookList)ImportFunction(_T("LoadPhoneBookList"));
	pLoadSearchPhoneBookListUsingSurname = (PLoadSearchPhoneBookList)ImportFunction(_T("LoadSearchPhoneBookListUsingSurname"));
	pLoadSearchPhoneBookListUsingTelephone = (PLoadSearchPhoneBookList)ImportFunction(_T("LoadSearchPhoneBookListUsingTelephone"));
	pLoadSearchPhoneBookListUsingStreet = (PLoadSearchPhoneBookList)ImportFunction(_T("LoadSearchPhoneBookListUsingStreet"));
	pEditPhoneBookNode = (PEditPhoneBookNode)ImportFunction(_T("EditPhoneBookNode"));
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

