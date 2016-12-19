#include "stdafx.h"
#include "ComboBox.h"


ComboBox::ComboBox(int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInst, unsigned int countString)
{
	this->currentCountString = 0;
	this->maxCountString = countString;
	int deltaNHeight = 15 * countString;
	hComboBox = CreateWindowEx(
		0,
		(LPCWSTR)WC_COMBOBOX, NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
		X,
		Y,
		nWidth,
		nHeight + deltaNHeight,
		hWndParent,
		NULL,
		hInst,
		NULL
	);	
}

bool ComboBox::AddString(tstring value)
{
	if (currentCountString < maxCountString)
	{
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)value.c_str());
		++currentCountString;
		return true;
	}	
	else
	{
		return false;
	}	
}

unsigned int ComboBox::GetCountString()
{
	return this->currentCountString;
}


ComboBox::~ComboBox()
{
}
