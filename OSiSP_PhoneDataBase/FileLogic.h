#pragma once

#include "CommonTTypes.h"
#include "PhoneBookNode.h"
#include "Convert.h"
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class FileLogic
{
public:	
	static vector<PhoneBookNode*>* GetPhoneBookList(LPTSTR fileName);
	static void WritePhoneBookList(LPTSTR fileName, vector<PhoneBookNode*>* phoneBookList);
private:
	static HANDLE hMutex;
	static unsigned long long freeNumber;
	static unsigned long long GetFreeNumber();
};

