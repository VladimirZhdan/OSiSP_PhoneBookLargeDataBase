#pragma once

#include "CommonTTypes.h"
#include "PhoneBookNode.h"
#include "Convert.h"
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class FileMappingLogic
{
public:	
	FileMappingLogic(LPTSTR fileName);
	unsigned long GetCountOfPhoneBookNode();
	PhoneBookNode *GetPhoneBookNode(unsigned long index);
	vector<PhoneBookNode*>* GetSearchPhoneBookList(PhoneBookNode *searchedPhoneBookNode);
	~FileMappingLogic();
private:
	void Initialization(LPTSTR fileName);	
	void SetOffsetOfPhoneBookNodeInFile();
	void CompareStrings(LPTSTR searhedStr, LPTSTR descStr, bool &isFind);

	struct DataBaseFileMapping
	{
		HANDLE hImputFile;
		char * imputFileBuffer;
		HANDLE hFileMapping;
		__int64 inputFileSize;
		DWORD bytesInBlock;
	};

	DataBaseFileMapping dataBaseFileMapping;
	bool isDataBaseFileMappingInit;
	vector<long> offsetOfPhoneBookNodeInFile;
};

