#pragma once

#include "CommonTTypes.h"
#include "PhoneBookNode.h"
#include <vector>

typedef unsigned long (WINAPI * PLoadCountOfPhoneBookNode)(LPTSTR fileName);
typedef PhoneBookNode* (WINAPI * PLoadPhoneBookNode)(unsigned long index);
typedef std::vector<PhoneBookNode*>* (WINAPI * PLoadSearchPhoneBookList)(PhoneBookNode *searchedPhoneBookNode);


class PhoneDataBase
{
public:
	PhoneDataBase(HWND hWnd, LPTSTR libraryFilePath);
	bool IsReadyToWork();	
	unsigned long LoadCountOfPhoneBookNode();
	PhoneBookNode* LoadPhoneBookNode(unsigned long index);
	std::vector<PhoneBookNode*>* LoadSearchPhoneBookList(PhoneBookNode *searchedPhoneBookNode);
	~PhoneDataBase();
private:
	//Methods

	void Init();
	FARPROC ImportFunction(tstring functionName);

	//Fields

	bool isReadyToWork;
	HWND hWnd;
	LPTSTR libraryFilePath;
	HINSTANCE hLibrary;	
	PLoadCountOfPhoneBookNode pLoadCountOfPhoneBookNode;
	PLoadPhoneBookNode pLoadPhoneBookNode;	
	PLoadSearchPhoneBookList pLoadSearchPhoneBookList;
};

