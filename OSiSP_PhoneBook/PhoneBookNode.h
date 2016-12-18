#pragma once

class PhoneBookNode
{
public:
	PhoneBookNode(LPTSTR phoneNumber, LPTSTR surname, LPTSTR name, LPTSTR patronymic, LPTSTR street, LPTSTR house, LPTSTR building, LPTSTR apartment);
	void SetStreet(LPTSTR street);
	void SetHouse(LPTSTR house);
	void SetBuilding(LPTSTR building);
	void SetApartment(LPTSTR apartment);
	~PhoneBookNode();
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

