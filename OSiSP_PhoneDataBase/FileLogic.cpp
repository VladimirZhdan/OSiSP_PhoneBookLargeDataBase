#include "stdafx.h"
#include "FileLogic.h"

vector<PhoneBookNode*>* FileLogic::GetPhoneBookList(LPTSTR fileName)
{
	vector<PhoneBookNode*>* resultList = new vector<PhoneBookNode*>();

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
			resultList->push_back(new PhoneBookNode(phoneNumber, surname, name, patronymic, street, house, building, apartment));
		}
		
	}

	streamReader.close();
	
	return resultList;
}
