#pragma once

#include "CommonTTypes.h"
#include "PhoneBookNode.h"
#include "TrieNode.h"
#include <vector>
#include <tchar.h>

using namespace std;

enum class TRIE_TYPE {
	SURNAME,
	TELEPHONE,
	STREET
};

class Trie
{
public:
	Trie(TRIE_TYPE type, vector<PhoneBookNode*>* phoneBookList);
	TRIE_TYPE GetTrieType();
	vector<PhoneBookNode*>* GetSearchPhoneBookList(LPTSTR searchKey);
	~Trie();
private:
	void InitializationTree(vector<PhoneBookNode*>* phoneBookList);
	void AddTrieNode(LPTSTR key, PhoneBookNode* phoneBookNode);
	TrieNode* GetLeafTreeNode(LPTSTR key);
	void GetTrieNodePhoneBookNodeList(TrieNode* trieNode, vector<PhoneBookNode*>* phoneTrieNodeList);
	TrieNode *headTrie;
	TRIE_TYPE typeTrie;
};

