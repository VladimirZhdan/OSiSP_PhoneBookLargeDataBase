#pragma once

#include <CommCtrl.h>
#include "CommonTTypes.h"

class ComboBox
{
public:
	ComboBox(int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInst, unsigned int countString);
	bool AddString(tstring value);
	unsigned int GetCountString();
	tstring GetSelectedItem();
	~ComboBox();
private:
	HWND hComboBox;
	unsigned int maxCountString;
	unsigned int currentCountString;
};

