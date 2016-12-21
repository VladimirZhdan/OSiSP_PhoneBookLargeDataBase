#pragma once

#include <tchar.h>

class PhoneBookNode
{
public:		
	PhoneBookNode(LPTSTR phoneNumber, LPTSTR surname, LPTSTR name, LPTSTR patronymic, LPTSTR street, LPTSTR house, LPTSTR building, LPTSTR apartment);
	void SetStreet(LPTSTR street);
	void SetHouse(LPTSTR house);
	void SetBuilding(LPTSTR building);
	void SetApartment(LPTSTR apartment);
	LPTSTR GetPhoneNumber();
	LPTSTR GetSurname();
	LPTSTR GetName();
	LPTSTR GetPatronymic();
	LPTSTR GetStreet();
	LPTSTR GetHouse();
	LPTSTR GetBuilding();
	LPTSTR GetApartment();
	~PhoneBookNode();
	unsigned long long number;
private:
	LPTSTR phoneNumber;
	LPTSTR surname;
	LPTSTR name;
	LPTSTR patronymic;
	LPTSTR street;
	LPTSTR house;
	LPTSTR building;
	LPTSTR apartment;
};

