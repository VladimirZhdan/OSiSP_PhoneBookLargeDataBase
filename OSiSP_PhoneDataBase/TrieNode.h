#pragma once

#include "PhoneBookNode.h"
#include <vector>

using namespace std;

class TrieNode
{
public:
	TrieNode(TCHAR key);
	void AddPhoneBookNode(PhoneBookNode *phoneBookNode);
	void AddSonTrieNode(TCHAR key);
	bool CointainsSonTrieNode(TCHAR key);
	TrieNode *GetSonTrieNode(TCHAR key);
	vector<PhoneBookNode*> GetPhoneBookNodeList();
	vector<TrieNode*> GetSonTrieNodeList();
	~TrieNode();
private:
	//Fields

	TCHAR key;	
	vector<PhoneBookNode*> phoneBookNodeList;
	vector<TrieNode*> sonTrieNodeList;

};

