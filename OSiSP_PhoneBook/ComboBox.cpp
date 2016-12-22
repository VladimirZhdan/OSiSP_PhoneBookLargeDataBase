#include "stdafx.h"
#include "ComboBox.h"


ComboBox::ComboBox(int X, int Y, int nWidth, int nHeight, HWND hWndParent, int cBoxIdentifier, HINSTANCE hInst, unsigned int countString)
{
	this->currentCountString = 0;
	this->maxCountString = countString;
	int deltaNHeight;
	if (countString > 10)
	{
		deltaNHeight = 15 * 10;
	}
	else
	{
		deltaNHeight = 15 * countString;
	}
	 
	hComboBox = CreateWindowEx(
		0,
		(LPCWSTR)WC_COMBOBOX, NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | CBS_SIMPLE | WS_VSCROLL,
		X,
		Y,
		nWidth,
		nHeight + deltaNHeight,
		hWndParent,
		(HMENU)cBoxIdentifier,
		hInst,
		NULL
	);	
	TCHAR cueBanner[] = _T("Выберите категорию");
	int result = SendMessage(hComboBox, CB_SETCUEBANNER, 0, (LPARAM)cueBanner);
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

tstring ComboBox::GetSelectedItem()
{		
	unsigned int indexSelectedItem = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
	if (indexSelectedItem != CB_ERR)
	{
		int lengthSelectedItemString = SendMessage(hComboBox, CB_GETLBTEXTLEN, indexSelectedItem, 0);
		TCHAR selectedItemString[256];		
		SendMessage(hComboBox, CB_GETLBTEXT, indexSelectedItem, (LPARAM)selectedItemString);
		tstring result(selectedItemString);		
		return result;
	}
	else
	{
		return tstring(_T(""));
	}
}

long ComboBox::GetIndexSelectedItem()
{
	unsigned int result = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
	if (result != CB_ERR)
	{
		return result;
	}
	else
	{
		return -1;
	}	
}


ComboBox::~ComboBox()
{
}
