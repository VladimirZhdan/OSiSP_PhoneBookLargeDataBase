#include "stdafx.h"
#include "TrieNode.h"


TrieNode::TrieNode(TCHAR key)
{
	this->key = key;
}

void TrieNode::AddPhoneBookNode(PhoneBookNode *phoneBookNode)
{
	phoneBookNodeList.push_back(phoneBookNode);
}

void TrieNode::AddSonTrieNode(TCHAR key)
{
	if (!CointainsSonTrieNode(key))
	{
		TrieNode *newTrieNode = new TrieNode(key);
		sonTrieNodeList.push_back(newTrieNode);
	}	
}


TrieNode::~TrieNode()
{
	for (int i = 0; i < sonTrieNodeList.size(); ++i)
	{
		delete(sonTrieNodeList[i]);
	}
}

bool TrieNode::CointainsSonTrieNode(TCHAR key)
{
	bool result = false;
	for (int i = 0; (i < sonTrieNodeList.size()) && (!result); ++i)
	{
		if (sonTrieNodeList[i]->key == key)
		{
			result = true;
		}
	}

	return result;
}

TrieNode * TrieNode::GetSonTrieNode(TCHAR key)
{	
	TrieNode *result = nullptr;
	bool isFind = false;
	for (int i = 0; (i < sonTrieNodeList.size()) && (!isFind); ++i)
	{
		if (sonTrieNodeList[i]->key == key)
		{
			result = sonTrieNodeList[i];
			isFind = true;
		}
	}
	return result;
}

vector<PhoneBookNode*> TrieNode::GetPhoneBookNodeList()
{
	return phoneBookNodeList;	
}

vector<TrieNode*> TrieNode::GetSonTrieNodeList()
{
	return sonTrieNodeList;
}
