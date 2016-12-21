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

void WINAPI InitializationLibrary(LPTSTR fileName, bool isUpdate = false);
void WINAPI InitializationIndexStructures(bool isUpdate = false);
void WINAPI DeleteTrie(Trie *desc);
void WINAPI ClearPhoneBookList();

std::vector<PhoneBookNode*>* WINAPI LoadPhoneBookList(LPTSTR fileName)
{
	if (!isLibraryInit)
	{
		InitializationLibrary(fileName);
	}
	else
	{
		InitializationLibrary(fileName, true);
	}
	return phoneBookList;
}

void WINAPI InitializationLibrary(LPTSTR fileName, bool isUpdate)
{
	if (isUpdate)
	{
		ClearPhoneBookList();
	}
	phoneBookList = FileLogic::GetPhoneBookList(fileName);
	InitializationIndexStructures(isUpdate);
	isLibraryInit = true;
}

void WINAPI InitializationIndexStructures(bool isUpdate)
{
	if (isUpdate)
	{
		DeleteTrie(surnameTrie);
		DeleteTrie(telephoneTrie);
		DeleteTrie(streetTrie);
	}
	surnameTrie = new Trie(TRIE_TYPE::SURNAME, phoneBookList);
	telephoneTrie = new Trie(TRIE_TYPE::TELEPHONE, phoneBookList);
	streetTrie = new Trie(TRIE_TYPE::STREET, phoneBookList);
}

void WINAPI DeleteTrie(Trie *desc)
{
	if (desc != NULL)
	{
		delete(desc);
	}
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

void WINAPI EditPhoneBookNode(PhoneBookNode *phoneBookNode, LPTSTR libraryFileName)
{
	bool isFind = false;
	for (int i = 0; (i < phoneBookList->size()) && (!isFind); ++i)
	{
		if ((*phoneBookList)[i]->number == phoneBookNode->number)
		{
			(*phoneBookList)[i] = phoneBookNode;
			isFind = true;
		}
	}
	if (isFind)
	{
		FileLogic::WritePhoneBookList(libraryFileName, phoneBookList);
		InitializationIndexStructures(true);
	}
}

void WINAPI ClearPhoneBookList()
{
	for (int i = 0; i < phoneBookList->size(); ++i)
	{
		delete((*phoneBookList)[i]);
	}
	delete phoneBookList;
	phoneBookList = NULL;
}