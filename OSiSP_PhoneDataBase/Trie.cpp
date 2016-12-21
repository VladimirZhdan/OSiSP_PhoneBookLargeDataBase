#include "stdafx.h"
#include "Trie.h"


Trie::Trie(TRIE_TYPE type, vector<PhoneBookNode*>* phoneBookList)
{
	this->typeTrie = type;
	headTrie = new TrieNode(TEXT(' '));
	InitializationTree(phoneBookList);
}

TRIE_TYPE Trie::GetTrieType()
{
	return this->typeTrie;
}

vector<PhoneBookNode*>* Trie::GetSearchPhoneBookList(LPTSTR searchKey)
{
	vector<PhoneBookNode*>* resultSearchList = new vector<PhoneBookNode*>();

	TrieNode *leafTrieNode = GetLeafTreeNode(searchKey);
	if (leafTrieNode != nullptr)
	{
		GetTrieNodePhoneBookNodeList(leafTrieNode, resultSearchList);	
	}	

	return resultSearchList;
}


Trie::~Trie()
{
	delete(headTrie);
}

void Trie::InitializationTree(vector<PhoneBookNode*>* phoneBookList)
{
	for (int i = 0; i < phoneBookList->size(); ++i)
	{
		LPTSTR key = _T("");
		switch (typeTrie)
		{
		case TRIE_TYPE::SURNAME:
			key = (*phoneBookList)[i]->GetSurname();
			break;
		case TRIE_TYPE::TELEPHONE:
			key = (*phoneBookList)[i]->GetPhoneNumber();
			break;
		case TRIE_TYPE::STREET:
			key = (*phoneBookList)[i]->GetStreet();
			break;		
		}
		AddTrieNode(key, (*phoneBookList)[i]);
	}
}

void Trie::AddTrieNode(LPTSTR key, PhoneBookNode * phoneBookNode)
{
	TrieNode *currentTrieNode = headTrie;
	for (int i = 0; i < _tcslen(key); ++i)
	{
		if (!currentTrieNode->CointainsSonTrieNode(key[i]))
		{
			currentTrieNode->AddSonTrieNode(key[i]);			
		}		
		currentTrieNode = currentTrieNode->GetSonTrieNode(key[i]);
	}
	currentTrieNode->AddPhoneBookNode(phoneBookNode);
}

TrieNode * Trie::GetLeafTreeNode(LPTSTR key)
{
	TrieNode *currentTrieNode = headTrie;
	bool isFind = true;
	for (int i = 0; (i < _tcslen(key)) && (isFind); ++i)
	{
		if (currentTrieNode->CointainsSonTrieNode(key[i]))
		{
			currentTrieNode = currentTrieNode->GetSonTrieNode(key[i]);
		}
		else
		{
			isFind = false;
			currentTrieNode = nullptr;
		}		
	}	
	return currentTrieNode;
}

void Trie::GetTrieNodePhoneBookNodeList(TrieNode * trieNode, vector<PhoneBookNode*>* phoneTrieNodeList)
{
	vector<PhoneBookNode*> trieNodePhoneBookList = trieNode->GetPhoneBookNodeList();
	for (int i = 0; i < trieNodePhoneBookList.size(); ++i)
	{
		phoneTrieNodeList->push_back(trieNodePhoneBookList[i]);
	}

	vector<TrieNode*> sonTrieNodeList = trieNode->GetSonTrieNodeList();
	for (int i = 0; i < sonTrieNodeList.size(); ++i)
	{
		GetTrieNodePhoneBookNodeList(sonTrieNodeList[i], phoneTrieNodeList);
	}
}
