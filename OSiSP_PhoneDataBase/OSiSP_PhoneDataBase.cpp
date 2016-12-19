// OSiSP_PhoneDataBase.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include <vector>


//own files
#include "PhoneBookNode.h"
#include "FileLogic.h"
#include "Trie.h"

bool isLibraryInit = false;
Trie *surnameTrie;
Trie *telephoneTrie;
Trie *streetTrie;
std::vector<PhoneBookNode*>* phoneBookList;

void WINAPI InitializationLibrary(LPTSTR fileName);

std::vector<PhoneBookNode*>* WINAPI LoadPhoneBookList(LPTSTR fileName)
{
	if (!isLibraryInit)
	{
		InitializationLibrary(fileName);
	}
	return phoneBookList;
}

void WINAPI InitializationLibrary(LPTSTR fileName)
{
	phoneBookList = FileLogic::GetPhoneBookList(fileName);
	surnameTrie = new Trie(TRIE_TYPE::SURNAME, phoneBookList);
	telephoneTrie = new Trie(TRIE_TYPE::TELEPHONE, phoneBookList);
	streetTrie = new Trie(TRIE_TYPE::STREET, phoneBookList);
	isLibraryInit = true;
}

std::vector<PhoneBookNode*>* WINAPI LoadSearchPhoneBookListUsingSurname(LPTSTR surname, LPTSTR libraryFilePath)
{
	if (!isLibraryInit)
	{
		InitializationLibrary(libraryFilePath);
	}
	return surnameTrie->GetSearchPhoneBookList(surname);
}

std::vector<PhoneBookNode*>* WINAPI LoadSearchPhoneBookListUsingTelephone(LPTSTR telephone, LPTSTR libraryFilePath)
{
	if (!isLibraryInit)
	{
		InitializationLibrary(libraryFilePath);
	}
	return telephoneTrie->GetSearchPhoneBookList(telephone);
}

std::vector<PhoneBookNode*>* WINAPI LoadSearchPhoneBookListUsingStreet(LPTSTR street, LPTSTR libraryFileName)
{
	if (!isLibraryInit)
	{
		InitializationLibrary(libraryFileName);
	}
	return streetTrie->GetSearchPhoneBookList(street);
}