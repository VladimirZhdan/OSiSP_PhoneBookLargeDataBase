// OSiSP_PhoneDataBase.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include <vector>


//own files
#include "PhoneBookNode.h"
#include "FileMappingLogic.h"

bool isLibraryInit = false;
FileMappingLogic *fileMappingLogic;

void WINAPI InitializationLibrary(LPTSTR fileName);

unsigned long WINAPI LoadCountOfPhoneBookNode(LPTSTR fileName)
{
	if (!isLibraryInit)
	{
		InitializationLibrary(fileName);
	}	
	return fileMappingLogic->GetCountOfPhoneBookNode();
}

void WINAPI InitializationLibrary(LPTSTR fileName)
{
	fileMappingLogic = new FileMappingLogic(fileName);
	isLibraryInit = true;
}

PhoneBookNode* WINAPI LoadPhoneBookNode(unsigned long index)
{
	if (isLibraryInit)
	{
		return fileMappingLogic->GetPhoneBookNode(index);
	}
	else
	{
		return nullptr;
	}
}

std::vector<PhoneBookNode*>* WINAPI LoadSearchPhoneBookList(PhoneBookNode *searchedPhoneBookNode)
{
	return fileMappingLogic->GetSearchPhoneBookList(searchedPhoneBookNode);
}