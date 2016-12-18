#pragma once

#include "CommonTTypes.h"
#include "PhoneBookNode.h"
#include <vector>

typedef std::vector<PhoneBookNode*>* (WINAPI * PLoadPhoneBookList)(LPTSTR fileName);

class PhoneDataBase
{
public:
	PhoneDataBase(HWND hWnd);
	bool IsReadyToWork();
	std::vector<PhoneBookNode*>* LoadPhoneBookList(LPTSTR fileName);
	~PhoneDataBase();
private:
	//Methods

	void Init();
	FARPROC ImportFunction(tstring functionName);

	//Fields

	bool isReadyToWork;
	HWND hWnd;
	HINSTANCE hLibrary;
	static const tstring libratyPath;
	PLoadPhoneBookList pLoadPhoneBookList;
};

