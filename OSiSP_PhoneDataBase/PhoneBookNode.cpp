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


PhoneBookNode::~PhoneBookNode()
{
}
