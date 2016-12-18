// OSiSP_PhoneDataBase.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include <vector>


//own files
#include "PhoneBookNode.h"
#include "FileLogic.h"

std::vector<PhoneBookNode*>* WINAPI LoadPhoneBookList(LPTSTR fileName)
{
	return FileLogic::GetPhoneBookList(fileName);
}