#include "stdafx.h"
#include "FileLogic.h"

HANDLE FileLogic::hMutex = CreateMutex(NULL, FALSE, _T("PhoneDataBase"));

unsigned long long FileLogic::freeNumber = 0;

unsigned long long FileLogic::GetFreeNumber()
{
	unsigned long long result = freeNumber;
	++freeNumber;
	return freeNumber;
}

vector<PhoneBookNode*>* FileLogic::GetPhoneBookList(LPTSTR fileName)
{
	vector<PhoneBookNode*>* resultList = new vector<PhoneBookNode*>();

	WaitForSingleObject(hMutex, INFINITE);

	ifstream streamReader(fileName, ifstream::in);

	if (streamReader)
	{		
		string tempString;
		while (!streamReader.eof())
		{
			LPTSTR phoneNumber = TEXT("");
			LPTSTR surname = TEXT("");
			LPTSTR name = TEXT("");
			LPTSTR patronymic = TEXT("");
			LPTSTR street = TEXT("");
			LPTSTR house = TEXT("");
			LPTSTR building = TEXT("");
			LPTSTR apartment = TEXT("");			
			if (getline(streamReader, tempString))
			{
				Convert::ConvertStringToLPTSTR(phoneNumber, tempString);
			}
			if (getline(streamReader, tempString))
			{
				Convert::ConvertStringToLPTSTR(surname, tempString);
			}
			if (getline(streamReader, tempString))
			{
				
				Convert::ConvertStringToLPTSTR(name, tempString);
			}
			if (getline(streamReader, tempString))
			{
				Convert::ConvertStringToLPTSTR(patronymic, tempString);
			}
			if (getline(streamReader, tempString))
			{
				Convert::ConvertStringToLPTSTR(street, tempString);
			}
			if (getline(streamReader, tempString))
			{
				Convert::ConvertStringToLPTSTR(house, tempString);
			}
			if (getline(streamReader, tempString))
			{
				Convert::ConvertStringToLPTSTR(building, tempString);
			}
			if (getline(streamReader, tempString))
			{
				Convert::ConvertStringToLPTSTR(apartment, tempString);
			}			
			PhoneBookNode *newItem = new PhoneBookNode(phoneNumber, surname, name, patronymic, street, house, building, apartment);
			newItem->number = GetFreeNumber();
			resultList->push_back(newItem);
			delete[] phoneNumber;
			delete[] surname;
			delete[] name;
			delete[] patronymic;
			delete[] street;
			delete[] house;
			delete[] building;
			delete[] apartment;
		}
		
	}

	streamReader.close();

	ReleaseMutex(hMutex);
	
	return resultList;
}

void FileLogic::WritePhoneBookList(LPTSTR fileName, vector<PhoneBookNode*>* phoneBookList)
{	
	WaitForSingleObject(hMutex, INFINITE);
	tofstream streamWriter(fileName, tofstream::trunc);	
	try
	{
		for (int i = 0; i < phoneBookList->size(); ++i)
		{
			streamWriter << (*phoneBookList)[i]->GetPhoneNumber() << endl;
			streamWriter << (*phoneBookList)[i]->GetSurname() << endl;
			streamWriter << (*phoneBookList)[i]->GetName() << endl;
			streamWriter << (*phoneBookList)[i]->GetPatronymic() << endl;
			streamWriter << (*phoneBookList)[i]->GetStreet() << endl;
			streamWriter << (*phoneBookList)[i]->GetHouse() << endl;
			streamWriter << (*phoneBookList)[i]->GetBuilding() << endl;
			streamWriter << (*phoneBookList)[i]->GetApartment();
			if (i < phoneBookList->size() - 1)
			{
				streamWriter << endl;
			}
		}
	}
	catch(...)
	{
		ReleaseMutex(hMutex);
		streamWriter.close();
		throw;
	}
	ReleaseMutex(hMutex);
	streamWriter.close();
}
