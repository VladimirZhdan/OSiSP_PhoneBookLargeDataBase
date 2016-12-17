#pragma once

#include <string>
#include <tchar.h>
#include "CommonTTypes.h"

using namespace std;

class Convert
{
public:
	static void ConvertStringToLPTSTR(LPTSTR &desc, const string src);
};

