#include "stdafx.h"
#include "PhoneBookNode.h"


PhoneBookNode::PhoneBookNode(LPTSTR phoneNumber, LPTSTR surname, LPTSTR name, LPTSTR patronymic, LPTSTR street, LPTSTR house, LPTSTR building, LPTSTR apartment)
{
	this->phoneNumber = phoneNumber;
	this->surname = surname;
	this->name = name;
	this->patronymic = patronymic;
	this->street = street;
	this->house = house;
	this->building = building;
	this->apartment = apartment;
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
}
