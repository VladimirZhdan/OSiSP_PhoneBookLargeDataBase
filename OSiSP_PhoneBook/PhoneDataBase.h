#pragma once

#include "CommonTTypes.h"
#include "PhoneBookNode.h"
#include <vector>

typedef std::vector<PhoneBookNode*>* (WINAPI * PLoadPhoneBookList)(LPTSTR fileName);

class PhoneDataBase
{
public:
	PhoneDataBase(HWND hWnd);
	~PhoneDataBase();
private:
	//Methods

	void Init();
	FARPROC ImportFunction(LPTSTR functionName);

	//Fields

	HWND hWnd;
	HINSTANCE hLibrary;
	static tstring libratyPath;
	PLoadPhoneBookList pLoadPhoneBookList;
};

