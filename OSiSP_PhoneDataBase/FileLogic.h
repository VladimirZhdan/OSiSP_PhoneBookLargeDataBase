#pragma once

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
};

