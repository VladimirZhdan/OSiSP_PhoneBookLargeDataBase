#include "stdafx.h"
#include "FileMappingLogic.h"

FileMappingLogic::FileMappingLogic(LPTSTR fileName)
{
	isDataBaseFileMappingInit = false;
	Initialization(fileName);
	if (isDataBaseFileMappingInit)
	{
		SetOffsetOfPhoneBookNodeInFile();
	}
}

unsigned long FileMappingLogic::GetCountOfPhoneBookNode()
{
	return offsetOfPhoneBookNodeInFile.size();	
}

PhoneBookNode * FileMappingLogic::GetPhoneBookNode(unsigned long index)
{
	PhoneBookNode *result = nullptr;
	if (isDataBaseFileMappingInit && (index <= GetCountOfPhoneBookNode()))
	{
		const int countOfFields = 8;				
		LPTSTR field = new TCHAR[256];

		int fieldNumber = 0;
		int currentFieldLength = 0;
		
		bool isPhoneBookNodeGet = false;

		tstring phoneNumber = TEXT("");
		tstring surname = TEXT("");
		tstring name = TEXT("");
		tstring patronymic = TEXT("");
		tstring street = TEXT("");
		tstring house = TEXT("");
		tstring building = TEXT("");
		tstring apartment = TEXT("");		
		
		bool isLastBlock = false;
		DWORD bytesInBlock = dataBaseFileMapping.bytesInBlock;
		__int64 offsetBlock = (offsetOfPhoneBookNodeInFile[index - 1] / bytesInBlock) * bytesInBlock;
		DWORD offsetInBlock = (offsetOfPhoneBookNodeInFile[index - 1] % bytesInBlock);
		for (__int64 fileSize = dataBaseFileMapping.inputFileSize - offsetBlock; (fileSize > 0) && (!isPhoneBookNodeGet); fileSize -= bytesInBlock)
		{
			if (fileSize <= bytesInBlock)
			{
				bytesInBlock = (DWORD)fileSize;
				isLastBlock = true;
			}

			LPCSTR tempFileBuffer = (LPCSTR)MapViewOfFile(dataBaseFileMapping.hFileMapping, FILE_MAP_READ, (DWORD)(offsetBlock >> 32), (DWORD)(offsetBlock & 0xFFFFFFFF), bytesInBlock);

			DWORD startIndex = 0;
			if (offsetInBlock != 0)
			{
				startIndex = offsetInBlock;
				offsetInBlock = 0;
			}			
			for (DWORD indexByteInBlock = startIndex; indexByteInBlock < bytesInBlock; ++indexByteInBlock)
			{
				if ((tempFileBuffer[indexByteInBlock] != '\n') && (tempFileBuffer[indexByteInBlock] != '\r') && !((indexByteInBlock == bytesInBlock - 1) && isLastBlock))
				{
					field[currentFieldLength] = tempFileBuffer[indexByteInBlock];
					++currentFieldLength;
					field[currentFieldLength] = L'\0';
				}
				else
				{
					if (indexByteInBlock == bytesInBlock - 1 && (isLastBlock))
					{
						field[currentFieldLength] = tempFileBuffer[indexByteInBlock];
						++currentFieldLength;
						field[currentFieldLength] = L'\0';
					}
					if (currentFieldLength != 0)
					{
						switch (fieldNumber)
						{
						case 0:
							phoneNumber = tstring(field);
							break;
						case 1:
							surname = tstring(field);
							break;
						case 2:
							name = tstring(field);
							break;
						case 3:
							patronymic = tstring(field);
							break;
						case 4:
							street = tstring(field);
							break;
						case 5:
							house = tstring(field);
							break;
						case 6:
							building = tstring(field);
							break;
						case 7:
							apartment = tstring(field);
							break;
						}
						++fieldNumber;
						currentFieldLength = 0;
						if (fieldNumber == countOfFields)
						{
							result = new PhoneBookNode((LPTSTR)phoneNumber.c_str(), (LPTSTR)surname.c_str(), (LPTSTR)name.c_str(), (LPTSTR)patronymic.c_str(),
								(LPTSTR)street.c_str(), (LPTSTR)house.c_str(), (LPTSTR)building.c_str(), (LPTSTR)apartment.c_str());
							isPhoneBookNodeGet = true;
						}
					}
				}
			}
			offsetBlock += bytesInBlock;
		}
	}
	return result;
}

vector<PhoneBookNode*>* FileMappingLogic::GetSearchPhoneBookList(PhoneBookNode * searchedPhoneBookNode)
{
	vector<PhoneBookNode*>* searchedPhoneBookList = new vector<PhoneBookNode*>();

	bool isFind;
	for (int i = 1; i <= offsetOfPhoneBookNodeInFile.size(); ++i)
	{
		isFind = true;
		PhoneBookNode *phoneBookNode = GetPhoneBookNode(i);
		CompareStrings(searchedPhoneBookNode->GetPhoneNumber(), phoneBookNode->GetPhoneNumber(), isFind);
		CompareStrings(searchedPhoneBookNode->GetSurname(), phoneBookNode->GetSurname(), isFind);
		CompareStrings(searchedPhoneBookNode->GetName(), phoneBookNode->GetName(), isFind);
		CompareStrings(searchedPhoneBookNode->GetPatronymic(), phoneBookNode->GetPatronymic(), isFind);
		CompareStrings(searchedPhoneBookNode->GetStreet(), phoneBookNode->GetStreet(), isFind);
		CompareStrings(searchedPhoneBookNode->GetHouse(), phoneBookNode->GetHouse(), isFind);
		CompareStrings(searchedPhoneBookNode->GetBuilding(), phoneBookNode->GetBuilding(), isFind);
		CompareStrings(searchedPhoneBookNode->GetApartment(), phoneBookNode->GetApartment(), isFind);
		if (isFind)
		{
			searchedPhoneBookList->push_back(phoneBookNode);
		}
		else
		{
			delete(phoneBookNode);
		}
	}

	return searchedPhoneBookList;
}

void FileMappingLogic::CompareStrings(LPTSTR searhedStr, LPTSTR descStr, bool &isFind)
{
	if (_tcslen(searhedStr) > 0)
	{
		if ((_tcscmp(searhedStr, descStr) != 0) && isFind)
		{
			isFind = false;
		}
	}
}

FileMappingLogic::~FileMappingLogic()
{
	if (isDataBaseFileMappingInit)
	{
		UnmapViewOfFile(dataBaseFileMapping.imputFileBuffer);
		dataBaseFileMapping.imputFileBuffer = NULL;		
		CloseHandle(dataBaseFileMapping.hFileMapping);		
		CloseHandle(dataBaseFileMapping.hImputFile);
	}
}

void FileMappingLogic::Initialization(LPTSTR fileName)
{
	SYSTEM_INFO sinf;
	GetSystemInfo(&sinf);
	dataBaseFileMapping.bytesInBlock = sinf.dwAllocationGranularity;

	dataBaseFileMapping.hImputFile = CreateFile(
		fileName,
		GENERIC_READ,
		FILE_SHARE_READ, 
		NULL, 
		OPEN_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL
	);

	if (dataBaseFileMapping.hImputFile == INVALID_HANDLE_VALUE)
	{
		dataBaseFileMapping.hImputFile = NULL;
		return;
	}

	DWORD fileSizeHigh;
	dataBaseFileMapping.inputFileSize = GetFileSize(dataBaseFileMapping.hImputFile, &fileSizeHigh);
	dataBaseFileMapping.inputFileSize += (((__int64)fileSizeHigh) << 32);

	dataBaseFileMapping.hFileMapping = CreateFileMapping(dataBaseFileMapping.hImputFile, NULL, PAGE_READONLY, 0, 0, L"FileMappingPhoneDatabase");
	
	if (dataBaseFileMapping.hFileMapping != NULL)
	{
		dataBaseFileMapping.imputFileBuffer = (char*)MapViewOfFile(dataBaseFileMapping.hFileMapping, FILE_MAP_READ, 0, 0, 0);
		if (dataBaseFileMapping.imputFileBuffer == NULL)
		{
			return;
		}
	}
	isDataBaseFileMappingInit = true;
}

void FileMappingLogic::SetOffsetOfPhoneBookNodeInFile()
{		
	const int countOfFields = 8;

	int fieldNumber = 0;
	bool isCurrentFieldHasNotNullLength = false;

	__int64 offset = 0;
	bool isNewNode = true;

	bool isLastBlock = false;
	DWORD bytesInBlock = dataBaseFileMapping.bytesInBlock;
	for (__int64 fileSize = dataBaseFileMapping.inputFileSize; fileSize > 0; fileSize -= bytesInBlock)
	{
		if (fileSize <= bytesInBlock)
		{
			bytesInBlock = (DWORD)fileSize;
			isLastBlock = true;
		}		
		
		LPCSTR tempFileBuffer = (LPCSTR)MapViewOfFile(dataBaseFileMapping.hFileMapping, FILE_MAP_READ, (DWORD)(offset >> 32), (DWORD)(offset &0xFFFFFFFF), bytesInBlock);

		for (DWORD indexByteInBlock = 0; indexByteInBlock < bytesInBlock; ++indexByteInBlock)
		{
			if ((tempFileBuffer[indexByteInBlock] != '\n') && (tempFileBuffer[indexByteInBlock] != '\r'))
			{
				if (isNewNode)
				{
					isNewNode = false;
					offsetOfPhoneBookNodeInFile.push_back(offset + indexByteInBlock);
				}
				isCurrentFieldHasNotNullLength = true;
			}
			else
			{
				if (isCurrentFieldHasNotNullLength)
				{
					++fieldNumber;
					isCurrentFieldHasNotNullLength = false;
					if (fieldNumber == countOfFields)
					{
						isNewNode = true;
						fieldNumber = 0;
					}
				}
			}			
		}
		if (isLastBlock)
		{
			++fieldNumber;
			isCurrentFieldHasNotNullLength = false;
			if (fieldNumber == countOfFields)
			{
				isNewNode = true;
				fieldNumber = 0;
			}
		}	
		offset += bytesInBlock;
	}
}
