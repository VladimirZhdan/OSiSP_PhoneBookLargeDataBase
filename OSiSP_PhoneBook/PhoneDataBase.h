#pragma once

#include "CommonTTypes.h"
#include "PhoneBookNode.h"
#include <vector>

typedef std::vector<PhoneBookNode*>* (WINAPI * PLoadPhoneBookList)(LPTSTR fileName);
typedef std::vector<PhoneBookNode*>* (WINAPI * PLoadSearchPhoneBookList)(LPTSTR searchKey, LPTSTR fileName);
typedef void(WINAPI * PEditPhoneBookNode)(PhoneBookNode *phoneBookNode, LPTSTR libraryFileName);

class PhoneDataBase
{
public:
	PhoneDataBase(HWND hWnd, LPTSTR libraryFilePath);
	bool IsReadyToWork();
	std::vector<PhoneBookNode*>* LoadPhoneBookList();
	std::vector<PhoneBookNode*>* LoadSearchPhoneBookListUsingSurname(LPTSTR searchSurname);
	std::vector<PhoneBookNode*>* LoadSearchPhoneBookListUsingTelephone(LPTSTR searchTelephone);
	std::vector<PhoneBookNode*>* LoadSearchPhoneBookListUsingStreet(LPTSTR searchStreet);
	void EditPhoneBookNode(PhoneBookNode *phoneBookNode);
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
	PLoadPhoneBookList pLoadPhoneBookList;
	PLoadSearchPhoneBookList pLoadSearchPhoneBookListUsingSurname;
	PLoadSearchPhoneBookList pLoadSearchPhoneBookListUsingTelephone;
	PLoadSearchPhoneBookList pLoadSearchPhoneBookListUsingStreet;
	PEditPhoneBookNode pEditPhoneBookNode;
};

