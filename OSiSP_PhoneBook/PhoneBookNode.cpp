#include "stdafx.h"
#include "PhoneBookNode.h"

PhoneBookNode::PhoneBookNode(LPTSTR phoneNumber, LPTSTR surname, LPTSTR name, LPTSTR patronymic, LPTSTR street, LPTSTR house, LPTSTR building, LPTSTR apartment)
{
	this->phoneNumber = new TCHAR[_tcslen(phoneNumber) + 1];
	this->surname = new TCHAR[_tcslen(surname) + 1];
	this->name = new TCHAR[_tcslen(name) + 1];
	this->patronymic = new TCHAR[_tcslen(patronymic) + 1];
	this->street = new TCHAR[_tcslen(street) + 1];
	this->house = new TCHAR[_tcslen(house) + 1];
	this->building = new TCHAR[_tcslen(building) + 1];
	this->apartment = new TCHAR[_tcslen(apartment) + 1];

	_tcscpy_s(this->phoneNumber, _tcslen(phoneNumber) + 1, phoneNumber);
	_tcscpy_s(this->surname, _tcslen(surname) + 1, surname);
	_tcscpy_s(this->name, _tcslen(name) + 1, name);
	_tcscpy_s(this->patronymic, _tcslen(patronymic) + 1, patronymic);
	_tcscpy_s(this->street, _tcslen(street) + 1, street);
	_tcscpy_s(this->house, _tcslen(house) + 1, house);
	_tcscpy_s(this->building, _tcslen(building) + 1, building);
	_tcscpy_s(this->apartment, _tcslen(apartment) + 1, apartment);

	this->number = 0;
}

void PhoneBookNode::SetStreet(LPTSTR street)
{
	this->street = street;
}

void PhoneBookNode::SetHouse(LPTSTR house)
{
	this->house = house;
}

void PhoneBookNode::SetBuilding(LPTSTR building)
{
	this->building = building;
}

void PhoneBookNode::SetApartment(LPTSTR apartment)
{
	this->apartment = apartment;
}

LPTSTR PhoneBookNode::GetPhoneNumber()
{
	return this->phoneNumber;
}

LPTSTR PhoneBookNode::GetSurname()
{
	return this->surname;
}

LPTSTR PhoneBookNode::GetName()
{
	return this->name;
}

LPTSTR PhoneBookNode::GetPatronymic()
{
	return this->patronymic;
}

LPTSTR PhoneBookNode::GetStreet()
{
	return this->street;
}

LPTSTR PhoneBookNode::GetHouse()
{
	return this->house;
}

LPTSTR PhoneBookNode::GetBuilding()
{
	return this->building;
}

LPTSTR PhoneBookNode::GetApartment()
{
	return this->apartment;
}


PhoneBookNode::~PhoneBookNode()
{
	delete[] phoneNumber;
	delete[] surname;
	delete[] name;
	delete[] patronymic;
	delete[] street;
	delete[] house;
	delete[] building;
	delete[] apartment;
}
